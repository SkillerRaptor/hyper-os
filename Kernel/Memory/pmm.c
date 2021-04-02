#include <Kernel/Memory/pmm.h>

#include <stdbool.h>
#include <string.h>
#include <AK/logger.h>
#include <Kernel/Memory/mm.h>

static uint8_t* bitmap = NULL;
static size_t last_used_index = 0;
static uintptr_t highest_page = 0;

#define SET_BIT(index) bitmap[index / BYTE_SIZE] |= (1u << (index % BYTE_SIZE))
#define CLEAR_BIT(index) bitmap[index / BYTE_SIZE] &= (~(1u << (index % BYTE_SIZE)))
#define GET_BIT(index) (bitmap[index / BYTE_SIZE] & (1u << (index % BYTE_SIZE)))

void pmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries)
{
	info("Kernel (pmm.c): Initializing physical memory manager...");
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		debug("Kernel (pmm.c): [Entry %d] [%X - %X]: Size %X, Type %X", i, memory_map[i].base, memory_map[i].base + memory_map[i].length, memory_map[i].length, memory_map[i].type);
		
		if (memory_map[i].type != STIVALE2_MMAP_USABLE &&
			memory_map[i].type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE &&
			memory_map[i].type != STIVALE2_MMAP_KERNEL_AND_MODULES)
			continue;
		
		uintptr_t top_address = memory_map[i].base + memory_map[i].length;
		
		if (top_address > highest_page)
			highest_page = top_address;
	}
	
	size_t memory_size = (highest_page + (PAGE_SIZE - 1)) / PAGE_SIZE;
	size_t bitmap_size = memory_size / BYTE_SIZE;
	warning("%d", bitmap_size);
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			continue;
		
		if (memory_map[i].length >= bitmap_size)
		{
			bitmap = (uint8_t*)(uintptr_t)((uintptr_t)memory_map[i].base + PHYSICAL_MEMORY_OFFSET);
			
			memset(bitmap, 0xFF, bitmap_size);
			
			memory_map[i].base += bitmap_size;
			memory_map[i].length -= bitmap_size;
			break;
		}
	}
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			continue;
		
		for (size_t length = 0; length < memory_map[i].length; length += PAGE_SIZE)
		{
			CLEAR_BIT((memory_map[i].base + length) / PAGE_SIZE);
		}
	}
	
	info("Kernel (pmm.c): Physical memory manager initialized...");
}

static void* pmm_inner_allocate(size_t page_count, size_t limit)
{
	debug("pmm_inner_allocate");
	size_t p = 0;
	
	while (last_used_index < limit)
	{
		debug("GET_BIT - %d - %d", last_used_index, last_used_index / BYTE_SIZE);
		if (GET_BIT(last_used_index) == false)
		{
			last_used_index++;
			debug("page_count");
			if (++p == page_count)
			{
				debug("page");
				size_t page = last_used_index - page_count;
				for (size_t i = page; i < last_used_index; i++)
				{
					debug("set");
					SET_BIT(i);
				}
				return (void*)(page * PAGE_SIZE);
			}
		}
		else
		{
			last_used_index++;
			p = 0;
		}
	}
	
	return NULL;
}

void* pmm_allocate_pages(size_t page_count)
{
	debug("pmm_allocate_pages");
	size_t index = last_used_index;
	void* address = pmm_inner_allocate(page_count, highest_page / PAGE_SIZE);
	if(address == NULL)
	{
		last_used_index = 0;
		address = pmm_inner_allocate(page_count, index);
	}
	return address;
}

void* pmm_callocate_pages(size_t page_count)
{
	debug("pmm_callocate_pages");
	uint8_t* address = (uint8_t*)pmm_allocate_pages(page_count);
	
	if (address == NULL)
	{
		return NULL;
	}
	
	uint64_t* ptr = (uint64_t*)(address + PHYSICAL_MEMORY_OFFSET);
	
	for (size_t i = 0; i < page_count * (PAGE_SIZE / sizeof(uint64_t)); i++)
	{
		ptr[i] = 0;
	}
	
	return address;
}

void pmm_free_pages(void* ptr, size_t page_count)
{
	debug("pmm_free_pages");
	size_t start_page = (size_t)ptr / PAGE_SIZE;
	for (size_t i = start_page; i < start_page + page_count; i++)
	{
		CLEAR_BIT(i);
	}
}