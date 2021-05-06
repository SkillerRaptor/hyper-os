#include "vmm.h"

#include "kalloc.h"
#include "memory.h"
#include "pmm.h"

#include <lib/logger.h>

static struct pagemap* kernel_pagemap;

void vmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries)
{
	info("Initializing VMM...");
	
	kernel_pagemap = vmm_create_new_pagemap();
	
	info(" The kernel pagemap was created!");
	
	/* Map memory */
	for (uintptr_t p = 0; p < 0x100000000; p += PAGE_SIZE)
	{
		vmm_map_page(kernel_pagemap, PHYSICAL_MEMORY_OFFSET + p, p, 0x03);
	}
	
	for (uintptr_t p = 0; p < 0x80000000; p += PAGE_SIZE)
	{
		vmm_map_page(kernel_pagemap, KERNEL_BASE_ADDRESS + p, p, 0x03);
	}
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		for (uintptr_t p = 0; p < memory_map[i].length; p += PAGE_SIZE)
		{
			vmm_map_page(kernel_pagemap, PHYSICAL_MEMORY_OFFSET + p, p, 0x03);
		}
	}
	
	info(" The memory for the kernel pagemap was mapped!");
	
	vmm_switch_pagemap(kernel_pagemap);
	
	info(" The pagemap was switched to the kernel pagemap!");
	
	info("Initializing VMM finished!");
}

struct pagemap* vmm_create_new_pagemap(void)
{
	struct pagemap* pagemap = kmalloc(sizeof(struct pagemap));
	pagemap->top_level = (uintptr_t) (uint64_t*) pmm_calloc(1);
	if (kernel_pagemap != NULL)
	{
		uintptr_t* top_level = (void*) ((uint8_t*) pagemap->top_level + PHYSICAL_MEMORY_OFFSET);
		uintptr_t* kernel_top_level = (void*) ((uint8_t*) kernel_pagemap->top_level + PHYSICAL_MEMORY_OFFSET);
		for (size_t i = 256; i < 512; i++)
		{
			top_level[i] = kernel_top_level[i];
		}
	}
	return pagemap;
}

void vmm_switch_pagemap(struct pagemap* pagemap)
{
	__asm__ volatile (
	"mov %%cr3, %0"
	:
	: "r" (pagemap->top_level)
	: "memory"
	);
}

static uintptr_t* get_next_level(uintptr_t* current_level, size_t entry, uint8_t allocate)
{
	uintptr_t ret;
	
	if (current_level[entry] & 0x1)
	{
		ret = current_level[entry] & ~((uintptr_t) 0xFFF);
	}
	else
	{
		if (allocate == 0)
		{
			return NULL;
		}
		
		ret = (uintptr_t) (uint64_t*) pmm_calloc(1);
		if (ret == 0)
		{
			return NULL;
		}
		
		current_level[entry] = ret | (1 << 0 | 1 << 1 | 1 << 2);
	}
	
	return (void*) (ret + PHYSICAL_MEMORY_OFFSET);
}

static uintptr_t* virtual2pte(struct pagemap* pagemap, uintptr_t virt_addr, uint8_t allocate)
{
	uintptr_t pml4_entry = (virt_addr & ((uintptr_t) 0x1FF << 39)) >> 39;
	uintptr_t pml3_entry = (virt_addr & ((uintptr_t) 0x1FF << 30)) >> 30;
	uintptr_t pml2_entry = (virt_addr & ((uintptr_t) 0x1FF << 21)) >> 21;
	uintptr_t pml1_entry = (virt_addr & ((uintptr_t) 0x1FF << 12)) >> 12;
	
	uintptr_t* pml4 = (void*) (pagemap->top_level + PHYSICAL_MEMORY_OFFSET);
	
	uintptr_t* pml3 = get_next_level(pml4, pml4_entry, allocate);
	if (pml3 == NULL)
	{
		return NULL;
	}
	
	uintptr_t* pml2 = get_next_level(pml3, pml3_entry, allocate);
	if (pml2 == NULL)
	{
		return NULL;
	}
	
	uintptr_t* pml1 = get_next_level(pml2, pml2_entry, allocate);
	if (pml1 == NULL)
	{
		return NULL;
	}
	
	return &pml1[pml1_entry];
}

uint8_t vmm_map_page(struct pagemap* pagemap, uintptr_t virtual_address, uintptr_t physical_address, uintptr_t flags)
{
	spinlock_lock(&pagemap->lock);
	
	uintptr_t* pte = virtual2pte(pagemap, virtual_address, 1);
	if (pte == NULL)
	{
		spinlock_unlock(&pagemap->lock);
		
		return 0;
	}
	
	*pte = physical_address | flags;
	
	spinlock_unlock(&pagemap->lock);
	
	return 1;
}
