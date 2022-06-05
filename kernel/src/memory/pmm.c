/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "memory/pmm.h"

#include "arch/boot.h"
#include "lib/logger.h"
#include "lib/math.h"
#include "lib/memory.h"
#include "memory/bitmap.h"

#include <stdint.h>

static uintptr_t s_highest_page = 0;
static size_t s_memory_offset = 0;
static struct bitmap s_bitmap = { 0 };

void pmm_init(void)
{
	struct limine_memmap_response *memory_map_response = boot_get_memory_map();
	if (memory_map_response == NULL)
	{
		return;
	}

	if (memory_map_response->entry_count == 0)
	{
		return;
	}

	struct limine_memmap_entry **memory_map = memory_map_response->entries;
	for (size_t i = 0; i < memory_map_response->entry_count; ++i)
	{
		if (memory_map[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		const uintptr_t highest_page = memory_map[i]->base + memory_map[i]->length;
		if (highest_page > s_highest_page)
		{
			s_highest_page = highest_page;
		}
	}

	struct limine_hhdm_response *hhdm_response = boot_get_hhdm();
	if (hhdm_response == NULL)
	{
		return;
	}

	s_memory_offset = hhdm_response->offset;

	s_bitmap.size = DIV_ROUND_UP(s_highest_page, PAGE_SIZE) / BYTE_SIZE;
	for (size_t i = 0; i < memory_map_response->entry_count; ++i)
	{
		if (memory_map[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		if (memory_map[i]->length >= s_bitmap.size)
		{
			s_bitmap.data = (uint8_t *) (memory_map[i]->base + s_memory_offset);

			bitmap_fill(&s_bitmap, 0xff),

				memory_map[i]->base += s_bitmap.size;
			memory_map[i]->length -= s_bitmap.size;

			break;
		}
	}

	for (size_t i = 0; i < memory_map_response->entry_count; ++i)
	{
		if (memory_map[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		for (uintptr_t j = 0; j < memory_map[i]->length; j += PAGE_SIZE)
		{
			bitmap_set(&s_bitmap, (memory_map[i]->base + j) / PAGE_SIZE, false);
		}
	}

	logger_info("Initialized PMM");
}

void *pmm_alloc(size_t page_count)
{
	size_t current_page_count = 0;
	for (size_t i = 0; i < s_bitmap.size * BYTE_SIZE; ++i)
	{
		if (bitmap_get(&s_bitmap, i))
		{
			current_page_count = 0;
			continue;
		}

		++current_page_count;
		if (current_page_count == page_count)
		{
			const size_t page = i - current_page_count;
			for (size_t j = page; j < i; ++j)
			{
				bitmap_set(&s_bitmap, i, true);
			}

			return (void *) (i * PAGE_SIZE);
		}
	}

	return NULL;
}

void *pmm_calloc(size_t page_count)
{
	void *ptr = pmm_alloc(page_count);
	if (ptr == NULL)
	{
		return NULL;
	}

	uint64_t *address = (uint64_t *) (ptr + s_memory_offset);
	for (size_t i = 0; i < page_count * (PAGE_SIZE / BYTE_SIZE); ++i)
	{
		address[i] = 0;
	}

	return ptr;
}

void pmm_free(void *ptr, size_t page_count)
{
	const uintptr_t page_address = (uintptr_t) ptr;
	const size_t page = page_address / PAGE_SIZE;
	for (size_t i = page; i < page + page_count; ++i)
	{
		bitmap_set(&s_bitmap, i, false);
	}
}

size_t pmm_get_hhdm_offset()
{
	return s_memory_offset;
}
