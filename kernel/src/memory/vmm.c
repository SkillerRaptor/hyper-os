/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "memory/vmm.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/memory.h"
#include "memory/kmalloc.h"
#include "memory/pmm.h"

#include <stdbool.h>

#define ATTRIBUTE_READ_WRITE (1 << 1)
#define ATTRIBUTE_PRESENT (1 << 0)

static struct page_map *s_kernel_page_map = NULL;

void vmm_init(void)
{
	s_kernel_page_map = vmm_create_page_map();

	for (uintptr_t address = PAGE_SIZE; address < 0x100000000;
			 address += PAGE_SIZE)
	{
		vmm_map_page(
			s_kernel_page_map,
			address,
			address + pmm_get_memory_offset(),
			ATTRIBUTE_READ_WRITE | ATTRIBUTE_PRESENT);
	}

	logger_info("VMM: Mapped higher half");

	struct limine_memmap_response *memory_map_response = boot_get_memory_map();
	assert(memory_map_response != NULL);
	assert(memory_map_response->entry_count != 0);

	for (size_t i = 0; i < memory_map_response->entry_count; i++)
	{
		for (uintptr_t address = 0;
				 address < memory_map_response->entries[i]->length;
				 address += PAGE_SIZE)
		{
			vmm_map_page(
				s_kernel_page_map,
				address,
				address + pmm_get_memory_offset(),
				ATTRIBUTE_READ_WRITE | ATTRIBUTE_PRESENT);
		}
	}

	logger_info("VMM: Mapped memory map");

	vmm_switch_page_map(s_kernel_page_map);

	logger_info("VMM: Loaded kernel page map");

	logger_info("VMM: Initialized");
}

struct page_map *vmm_create_page_map(void)
{
	struct page_map *page_map = kmalloc(sizeof(struct page_map));
	assert(page_map != NULL);

	page_map->top_level = (uintptr_t) pmm_calloc(1);
	assert(page_map->top_level != 0);

	return page_map;
}

static uintptr_t *vmm_get_next_level(uintptr_t *current_level, size_t entry)
{
	if (current_level[entry] & 0x1)
	{
		const uintptr_t level_entry = current_level[entry] & ~((uintptr_t) 0xFFF);
		return (uintptr_t *) (level_entry + pmm_get_memory_offset());
	}

	const uintptr_t next_level = (uintptr_t) pmm_calloc(1);
	if (next_level == 0)
	{
		return NULL;
	}

	current_level[entry] = next_level | 0b111;

	const uintptr_t level_entry = current_level[entry] & ~((uintptr_t) 0xFFF);
	return (uintptr_t *) (level_entry + pmm_get_memory_offset());
}

static uintptr_t *vmm_virtual_to_page_table_entry(
	struct page_map *page_map,
	uintptr_t virtual_address)
{
	uintptr_t *pml4 =
		(uintptr_t *) (page_map->top_level + pmm_get_memory_offset());

	const uintptr_t pml4_entry =
		(virtual_address & ((uintptr_t) 0x1FF << 39)) >> 39;
	uintptr_t *pml3 = vmm_get_next_level(pml4, pml4_entry);
	if (pml3 == NULL)
	{
		return NULL;
	}

	const uintptr_t pml3_entry =
		(virtual_address & ((uintptr_t) 0x1FF << 30)) >> 30;
	uintptr_t *pml2 = vmm_get_next_level(pml3, pml3_entry);
	if (pml2 == NULL)
	{
		return NULL;
	}

	const uintptr_t pml2_entry =
		(virtual_address & ((uintptr_t) 0x1FF << 21)) >> 21;
	uintptr_t *pml1 = vmm_get_next_level(pml2, pml2_entry);
	if (pml1 == NULL)
	{
		return NULL;
	}

	const uintptr_t pml1_entry =
		(virtual_address & ((uintptr_t) 0x1FF << 12)) >> 12;

	return &pml1[pml1_entry];
}

void vmm_map_page(
	struct page_map *page_map,
	uintptr_t physical_address,
	uintptr_t virtual_address,
	uintptr_t flags)
{
	uintptr_t *pte = vmm_virtual_to_page_table_entry(page_map, virtual_address);
	if (pte == NULL)
	{
		return;
	}

	*pte = physical_address | flags;
}

void vmm_switch_page_map(struct page_map *page_map)
{
	__asm__ __volatile__("mov %%cr3, %0" : : "r"(page_map->top_level) : "memory");
}

struct page_map *vmm_get_kernel_page_map(void)
{
	return s_kernel_page_map;
}
