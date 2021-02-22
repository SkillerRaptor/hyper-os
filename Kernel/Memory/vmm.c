#include <Kernel/Memory/vmm.h>

#include <stdlib.h>
#include <AK/logger.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/pmm.h>

static pagemap_t* kernel_pagemap;

static uintptr_t* vmm_get_next_level(uintptr_t* current_level, size_t entry)
{
	uintptr_t level;

	if (current_level[entry] & PAGEMAP_ATTRIBUTE_PRESENT)
	{
		level = current_level[entry] & ~((uintptr_t)0xfff);
	}
	else
	{
		level = (uintptr_t)pmm_callocate_pages(1);
		if (level == 0)
			return NULL;
		current_level[entry] = level | PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE | PAGEMAP_ATTRIBUTE_USER_SUPERVISOR;
	}

	return (uintptr_t*)level;
}

void vmm_init(struct stivale2_mmap_entry* memory_map, size_t memory_map_entries)
{
    info("VMM: Initializing virtual memory manager...");

	kernel_pagemap = vmm_create_new_pagemap();

	for (uintptr_t ptr = 0; ptr < 0x100000000; ptr += PAGE_SIZE)
		vmm_map_page(kernel_pagemap, (void*)ptr, (void*)(PHYSICAL_MEMORY_OFFSET + (uint64_t)ptr), PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);

	for (uintptr_t ptr = 0; ptr < 0x80000000; ptr += PAGE_SIZE)
		vmm_map_page(kernel_pagemap, (void*)ptr, (void*)(KERNEL_BASE_ADDRESS + (uint64_t)ptr), PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);

	for (size_t i = 0; i < memory_map_entries; i++)
	{
		struct stivale2_mmap_entry entry = memory_map[i];
		for (uintptr_t ptr = 0; ptr < entry.length; ptr += PAGE_SIZE)
			vmm_map_page(kernel_pagemap, (void*)ptr, (void*)(PHYSICAL_MEMORY_OFFSET + (uint64_t)ptr), PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);
	}

    info("VMM: Virtual memory manager initialized...");

	vmm_switch_pagemap(kernel_pagemap);
}

pagemap_t* vmm_create_new_pagemap(void)
{
	pagemap_t* pagemap = (pagemap_t*)malloc(sizeof(pagemap_t));
	pagemap->top_level = (uintptr_t*)pmm_allocate_pages(1);
	return pagemap;
}

void vmm_switch_pagemap(pagemap_t* pagemap)
{
	asm volatile(
        "mov %%cr3, %0"
        :
        : "r" (pagemap->top_level)
        : "memory"
        );
}

void vmm_map_page(pagemap_t* pagemap, void* physical_address, void* virtual_address, uint16_t flags)
{
    uintptr_t pml4_entry = ((uintptr_t) virtual_address & ((uintptr_t) 0x1FF << 39)) >> 39;
    uintptr_t pml3_entry = ((uintptr_t) virtual_address & ((uintptr_t) 0x1FF << 30)) >> 30;
    uintptr_t pml2_entry = ((uintptr_t) virtual_address & ((uintptr_t) 0x1FF << 21)) >> 21;
    uintptr_t pml1_entry = ((uintptr_t) virtual_address & ((uintptr_t) 0x1FF << 12)) >> 12;

    uintptr_t* pml4 = pagemap->top_level;

	uintptr_t* pml3 = vmm_get_next_level(pml4, pml4_entry);
	if (pml3 == NULL)
		return;

	uintptr_t* pml2 = vmm_get_next_level(pml3, pml3_entry);
	if (pml2 == NULL)
		return;

	uintptr_t* pml1 = vmm_get_next_level(pml2, pml2_entry);
	if (pml1 == NULL)
		return;

	pml1[pml1_entry] = (uintptr_t)((uint64_t)physical_address | flags);
}