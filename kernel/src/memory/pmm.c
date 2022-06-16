/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "memory/pmm.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/math.h"
#include "lib/memory.h"
#include "memory/bitmap.h"
#include "scheduling/spinlock.h"

#include <stdint.h>

static uintptr_t s_highest_page = 0;
static size_t s_memory_offset = 0;
static struct bitmap s_bitmap = { 0 };
static struct spinlock s_lock = { 0 };

void pmm_init(void)
{
	struct limine_hhdm_response *hhdm_response = boot_get_hhdm();
	assert(hhdm_response != NULL);

	s_memory_offset = hhdm_response->offset;

	struct limine_memmap_response *memory_map_response = boot_get_memory_map();
	assert(memory_map_response != NULL);
	assert(memory_map_response->entry_count != 0);

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

	logger_info("PMM: Highest page found at 0x%016x", s_highest_page);

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

			bitmap_fill(&s_bitmap, 0xff);

			memory_map[i]->base += s_bitmap.size;
			memory_map[i]->length -= s_bitmap.size;

			logger_info(
				"PMM: Bitmap allocated at 0x%016x - 0x%016x",
				memory_map[i]->base,
				memory_map[i]->base + memory_map[i]->length);
			break;
		}
	}

	size_t total_memory = 0;
	size_t free_memory = 0;
	for (size_t i = 0; i < memory_map_response->entry_count; ++i)
	{
		total_memory += memory_map[i]->length;

		if (memory_map[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		free_memory += memory_map[i]->length;

		for (uintptr_t j = 0; j < memory_map[i]->length; j += PAGE_SIZE)
		{
			bitmap_set(&s_bitmap, (memory_map[i]->base + j) / PAGE_SIZE, false);
		}
	}

	total_memory /= 1024 * 1024;
	free_memory /= 1024 * 1024;

	logger_info("PMM: Total memory - %uMiB", total_memory);
	logger_info("PMM: Used memory - %uMiB", total_memory - free_memory);
	logger_info("PMM: Free memory - %uMiB", free_memory);
	logger_info("PMM: Initialized");
}

void *pmm_alloc(size_t page_count)
{
	spinlock_lock(&s_lock);

	assert(page_count != 0);

	size_t current_page_count = 0;
	for (size_t i = 0; i < s_highest_page / PAGE_SIZE; ++i)
	{
		if (bitmap_get(&s_bitmap, i))
		{
			current_page_count = 0;
			continue;
		}

		++current_page_count;
		if (current_page_count == page_count)
		{
			const size_t index = i + 1;
			const size_t page = index - page_count;
			for (size_t j = page; j < index; ++j)
			{
				bitmap_set(&s_bitmap, j, true);
			}

			spinlock_unlock(&s_lock);

			return (void *) (page * PAGE_SIZE);
		}
	}

	spinlock_unlock(&s_lock);

	return NULL;
}

void *pmm_calloc(size_t page_count)
{
	assert(page_count != 0);

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
	assert(ptr != NULL);
	assert(page_count != 0);

	const uintptr_t page_address = (uintptr_t) ptr;
	const size_t page = page_address / PAGE_SIZE;
	for (size_t i = page; i < page + page_count; ++i)
	{
		bitmap_set(&s_bitmap, i, false);
	}
}

size_t pmm_get_memory_offset()
{
	return s_memory_offset;
}
