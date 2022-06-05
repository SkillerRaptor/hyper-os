/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "memory/kmalloc.h"

#include "lib/math.h"
#include "lib/memory.h"
#include "memory/pmm.h"

#include <stdint.h>

struct allocation_header
{
	size_t page_count;
	size_t size;
};

void *kmalloc(size_t size)
{
	size_t page_count = DIV_ROUND_UP(size, PAGE_SIZE);

	uint8_t *ptr = (uint8_t *) pmm_calloc(page_count + 1);
	if (ptr == NULL)
	{
		return NULL;
	}

	ptr = ptr + pmm_get_hhdm_offset();

	struct allocation_header *header = (struct allocation_header *) ptr;
	ptr = ptr + PAGE_SIZE;

	header->page_count = page_count;
	header->size = size;

	return ptr;
}

void *kcalloc(size_t count, size_t size)
{
	void *ptr = kmalloc(count * size);
	memset(ptr, 0x00, count * size);
	return ptr;
}

void *krealloc(void *ptr, size_t size)
{
	if (ptr == NULL)
	{
		return kmalloc(size);
	}

	uint8_t *header_address = (uint8_t *) ptr - PAGE_SIZE;
	struct allocation_header *header =
		(struct allocation_header *) header_address;

	if (DIV_ROUND_UP(header->size, PAGE_SIZE) == DIV_ROUND_UP(size, PAGE_SIZE))
	{
		header->size = size;
		return ptr;
	}

	void *new_ptr = kmalloc(size);
	if (new_ptr == NULL)
	{
		return NULL;
	}

	memcpy(new_ptr, ptr, (header->size > size) ? size : header->size);
	kfree(ptr);

	return new_ptr;
}

void kfree(void *ptr)
{
	uint8_t *header_address = (uint8_t *) ptr - PAGE_SIZE;
	struct allocation_header *header =
		(struct allocation_header *) header_address;

	const size_t page_count = header->page_count + 1;
	pmm_free((void *) (header_address - pmm_get_hhdm_offset()), page_count);
}
