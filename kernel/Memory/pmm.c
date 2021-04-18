#include "pmm.h"

#include "bitmap.h"
#include "memory.h"

#include <utilities/builtins.h>
#include <utilities/logger.h>
#include <utilities/math.h>

static uint8_t* bitmap;
static size_t last_used_index = 0;
static uintptr_t highest_page = 0;

void pmm_init(struct stivale2_memory_map_entry* memory_map, size_t memory_map_entries)
{
	info("Initializing PMM...");
	
	/* Find biggest memory map entry */
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		debug("[Entry %d] [%x - %x]: Size: %x - Type: %x", i, memory_map[i].base,
		      memory_map[i].base + memory_map[i].length, memory_map[i].length, memory_map[i].type);
		
		if (memory_map[i].type != STIVALE2_MEMORY_MAP_USABLE)
		{
			continue;
		}
		
		uintptr_t top = memory_map[i].base + memory_map[i].length;
		if (top > highest_page)
		{
			highest_page = top;
		}
	}
	
	info(" The biggest memory map entry was found!");
	
	/* Find place to put bitmap in */
	size_t bitmap_size = DIV_ROUNDUP(highest_page, PAGE_SIZE) / 8;
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MEMORY_MAP_USABLE)
		{
			continue;
		}
		
		if (memory_map[i].length >= bitmap_size)
		{
			bitmap = (void*) (memory_map[i].base + PHYSICAL_MEMORY_OFFSET);
			
			memset(bitmap, 0xFF, bitmap_size);
			
			memory_map[i].length -= bitmap_size;
			memory_map[i].base += bitmap_size;
			
			break;
		}
	}
	
	info(" The bitmap was placed into a memory map entry!");
	
	/* Free usable memory */
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MEMORY_MAP_USABLE)
		{
			continue;
		}
		
		for (uintptr_t j = 0; j < memory_map[i].length; j += PAGE_SIZE)
		{
			bitmap_set_bit(bitmap, (memory_map[i].base + j) / PAGE_SIZE, 0);
		}
	}
	
	info(" The usable memory was marked as free!");
	
	info("Initializing PMM finished!");
}

static void* pmm_inner_alloc(size_t count, size_t limit)
{
	size_t p = 0;
	
	while (last_used_index < limit)
	{
		if (!bitmap_get_bit(bitmap, last_used_index++))
		{
			if (++p == count)
			{
				size_t page = last_used_index - count;
				for (size_t i = page; i < last_used_index; i++)
				{
					bitmap_set_bit(bitmap, i, 1);
				}
				return (void*) (page * PAGE_SIZE);
			}
		}
		else
		{
			p = 0;
		}
	}
	
	return NULL;
}

void* pmm_alloc(size_t count)
{
	size_t l = last_used_index;
	void* ret = pmm_inner_alloc(count, highest_page / PAGE_SIZE);
	if (ret == NULL)
	{
		last_used_index = 0;
		ret = pmm_inner_alloc(count, l);
	}
	
	return ret;
}

void* pmm_calloc(size_t count)
{
	char* ret = (char*) pmm_alloc(count);
	
	if (ret == NULL)
	{
		return NULL;
	}
	
	uint64_t* ptr = (uint64_t*) (ret + PHYSICAL_MEMORY_OFFSET);
	
	for (size_t i = 0; i < count * (PAGE_SIZE / sizeof(uint64_t)); i++)
	{
		ptr[i] = 0x0;
	}
	
	return ret;
}

void pmm_free(void* ptr, size_t count)
{
	size_t page = (size_t) ptr / PAGE_SIZE;
	for (size_t i = page; i < page + count; i++)
	{
		bitmap_set_bit(bitmap, i, 0);
	}
}