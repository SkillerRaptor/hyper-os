#include <Kernel/Memory/vmm.h>

#include <stdbool.h>
#include <AK/logger.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/kmm.h>
#include <Kernel/Memory/pmm.h>

static pagemap_t* kernel_pagemap;

static char hexTo_StringOutput[128];
static const char* to_string(uint64_t value){
	uint64_t* valPtr = &value;
	uint8_t* ptr;
	uint8_t tmp;
	uint8_t size = 8 * 2 - 1;
	for (uint8_t i = 0; i < size; i++){
		ptr = ((uint8_t*)valPtr + i);
		tmp = ((*ptr & 0xF0) >> 4);
		hexTo_StringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
		tmp = ((*ptr & 0x0F));
		hexTo_StringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
	}
	hexTo_StringOutput[size + 1] = 0;
	return hexTo_StringOutput;
}

void vmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries)
{
    info("Kernel (vmm.c): Initializing virtual memory manager...");

	kernel_pagemap = vmm_create_new_pagemap();
	
	for (uintptr_t ptr = 0; ptr < 0x100000000; ptr += PAGE_SIZE)
	{
		vmm_map_page(kernel_pagemap, ptr, ptr + PHYSICAL_MEMORY_OFFSET, PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);
		break;
	}
	
	/*
	for (uintptr_t ptr = 0; ptr < 0x80000000; ptr += PAGE_SIZE)
	{
		vmm_map_page(kernel_pagemap, ptr, ptr + KERNEL_BASE_ADDRESS, PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);
	}
	 */
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		for (uintptr_t ptr = 0; ptr < memory_map[i].length; ptr += PAGE_SIZE)
	    {
			//vmm_map_page(kernel_pagemap, ptr, ptr + PHYSICAL_MEMORY_OFFSET, PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE);
	    }
	}
	
	info("Kernel (vmm.c): Virtual memory manager initialized...");

	vmm_switch_pagemap(kernel_pagemap);
}

pagemap_t* vmm_create_new_pagemap(void)
{
	pagemap_t* pagemap = kmalloc(sizeof(pagemap_t));
	info("pagemap: %s", to_string((uint64_t)pagemap));
	info("pagemap size: %d", sizeof(pagemap_t));
	pagemap->top_level = pmm_callocate_pages(1);
	info("top_level: %s", to_string((uint64_t)pagemap->top_level));
	
	if(kernel_pagemap != NULL)
	{
		uintptr_t* top_level = pagemap->top_level + PHYSICAL_MEMORY_OFFSET;
		uintptr_t* kernel_top_level = kernel_pagemap->top_level + PHYSICAL_MEMORY_OFFSET;
		for(size_t i = 256; i < 512; i++)
		{
			top_level[i] = kernel_top_level[i];
		}
	}
	
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

static uintptr_t* vmm_get_next_level(uintptr_t* current_level, size_t entry, bool allocate)
{
	uintptr_t level;
	if (current_level[entry] & PAGEMAP_ATTRIBUTE_PRESENT)
	{
		level = current_level[entry] & ~((uintptr_t)0xFFF);
	}
	else
	{
		if (!allocate)
		{
			return NULL;
		}
		
		level = (uintptr_t)pmm_callocate_pages(1);
		if(level == 0)
		{
			return NULL;
		}
		
		current_level[entry] = level | PAGEMAP_ATTRIBUTE_PRESENT | PAGEMAP_ATTRIBUTE_READ_AND_WRITE | PAGEMAP_ATTRIBUTE_USER_SUPERVISOR;
	}
	
	return (void*)level + PHYSICAL_MEMORY_OFFSET;
}

static uintptr_t* virtual_to_page_entry(pagemap_t* pagemap, uintptr_t virtual_address, bool allocate)
{
	uintptr_t pml4_entry = (virtual_address & ((uintptr_t)0x1FF << 39)) >> 39;
	uintptr_t pml3_entry = (virtual_address & ((uintptr_t)0x1FF << 30)) >> 30;
	uintptr_t pml2_entry = (virtual_address & ((uintptr_t)0x1FF << 21)) >> 21;
	uintptr_t pml1_entry = (virtual_address & ((uintptr_t)0x1FF << 12)) >> 12;
	
	uintptr_t* pml4 = (void*)pagemap->top_level + PHYSICAL_MEMORY_OFFSET;
	if(pml4 == NULL)
	{
		error("Kernel (vmm.c): PML4 is null!");
		return NULL;
	}
	
	uintptr_t* pml3 = vmm_get_next_level(pml4, pml4_entry, allocate);
	if (pml3 == NULL)
	{
		error("Kernel (vmm.c): PML3 is null!");
		return NULL;
	}
	
	uintptr_t* pml2 = vmm_get_next_level(pml3, pml3_entry, allocate);
	if (pml2 == NULL)
	{
		error("Kernel (vmm.c): PML2 is null!");
		return NULL;
	}
	
	uintptr_t* pml1 = vmm_get_next_level(pml2, pml2_entry, allocate);
	if (pml1 == NULL)
	{
		error("Kernel (vmm.c): PML1 is null!");
		return NULL;
	}
	
	return &pml1[pml1_entry];
}

void vmm_map_page(pagemap_t* pagemap, uintptr_t physical_address, uintptr_t virtual_address, uintptr_t flags)
{
	info("pagemap: %s", to_string((uint64_t)pagemap));
	info("physical_address: %s", to_string((uint64_t)physical_address));
	info("virtual_address: %s", to_string((uint64_t)virtual_address));
	info("flags: %x", flags);
	uintptr_t* page_entry = virtual_to_page_entry(pagemap, virtual_address, true);
	if (page_entry == NULL)
	{
		error("Kernel (vmm.c): Page Entry is null!");
		return;
	}
	info("Pointer: %p", page_entry);
	return;
	
	*page_entry = physical_address | flags;
}