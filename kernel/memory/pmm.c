#include "pmm.h"

#include "bitmap.h"
#include "memory.h"

#include <lib/builtins.h>
#include <lib/logger.h>
#include <lib/math.h>
#include <synchronization/spinlock.h>

static struct bitmap bitmap;
static size_t last_used_index = 0;
static uintptr_t highest_page = 0;

static spinlock lock;

void pmm_init(struct stivale2_mmap_entry* memory_map, size_t memory_map_entries)
{
	info("PMM: Initializing...");
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		debug("[Entry %d] [%x - %x]: Size: %x - Type: %x", i, memory_map[i].base, memory_map[i].base + memory_map[i].length,
		      memory_map[i].length, memory_map[i].type);
		
		if (memory_map[i].type != STIVALE2_MMAP_USABLE)
		{
			continue;
		}
		
		uintptr_t top = memory_map[i].base + memory_map[i].length;
		if (top > highest_page)
		{
			highest_page = top;
		}
	}
	
	size_t bitmap_size = math_div_roundup(highest_page, PAGE_SIZE) / 8;
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MMAP_USABLE)
		{
			continue;
		}
		
		if (memory_map[i].length >= bitmap_size)
		{
			bitmap.data = (void*) (memory_map[i].base + PHYSICAL_MEMORY_OFFSET);
			bitmap.size = bitmap_size;
			
			memset(bitmap.data, 0xFF, bitmap_size);
			
			memory_map[i].length -= bitmap_size;
			memory_map[i].base += bitmap_size;
			
			break;
		}
	}
	
	for (size_t i = 0; i < memory_map_entries; i++)
	{
		if (memory_map[i].type != STIVALE2_MMAP_USABLE)
		{
			continue;
		}
		
		for (uintptr_t j = 0; j < memory_map[i].length; j += PAGE_SIZE)
		{
			bitmap_set_bit(&bitmap, (memory_map[i].base + j) / PAGE_SIZE, 0);
		}
	}
	
	info("PMM: Initializing finished!");
}

static void* pmm_internal_allocate(size_t count, size_t limit)
{
	size_t p = 0;
	
	while (last_used_index < limit)
	{
		if (!bitmap_get_bit(&bitmap, last_used_index++))
		{
			if (++p == count)
			{
				size_t page = last_used_index - count;
				for (size_t i = page; i < last_used_index; i++)
				{
					bitmap_set_bit(&bitmap, i, 1);
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

void* pmm_allocate(size_t count)
{
	spinlock_lock(&lock);
	
	size_t last_index = last_used_index;
	void* ret = pmm_internal_allocate(count, highest_page / PAGE_SIZE);
	if (ret == NULL)
	{
		last_used_index = 0;
		ret = pmm_internal_allocate(count, last_index);
	}
	
	spinlock_unlock(&lock);
	
	return ret;
}

void* pmm_callocate(size_t count)
{
	uint8_t* ret = (uint8_t*) pmm_allocate(count);
	
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
	spinlock_lock(&lock);
	
	size_t page = (size_t) ptr / PAGE_SIZE;
	for (size_t i = page; i < page + count; i++)
	{
		bitmap_set_bit(&bitmap, i, 0);
	}
	
	spinlock_unlock(&lock);
}
