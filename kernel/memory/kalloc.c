#include "kalloc.h"

#include "memory.h"
#include "pmm.h"

#include <lib/builtins.h>
#include <lib/logger.h>
#include <lib/math.h>

#include <stdint.h>

struct allocation_metadata
{
	size_t pages;
	size_t size;
};

void* kmalloc(size_t size)
{
	size_t page_count = math_div_roundup(size, PAGE_SIZE);
	
	uint8_t* ptr = (uint8_t*) pmm_callocate(page_count + 1);
	
	if (ptr == NULL)
	{
		return NULL;
	}
	
	ptr += PHYSICAL_MEMORY_OFFSET;
	
	struct allocation_metadata* metadata = (void*) ptr;
	ptr += PAGE_SIZE;
	
	metadata->pages = page_count;
	metadata->size = size;
	
	debug("kmalloc: %d bytes allocated!", size);
	
	return (void*) ptr;
}

void* kcalloc(size_t element_count, size_t size)
{
	void* ptr = kmalloc(element_count * size);
	memset(ptr, 0x00, element_count * size);
	return ptr;
}

void* krealloc(void* pointer, size_t size)
{
	if (!pointer)
	{
		return kmalloc(size);
	}
	
	struct allocation_metadata* metadata = (void*) (pointer - PAGE_SIZE);
	
	if (math_div_roundup(metadata->size, PAGE_SIZE) == math_div_roundup(size, PAGE_SIZE))
	{
		metadata->size = size;
		return pointer;
	}
	
	void* new_ptr = kmalloc(size);
	if (new_ptr == NULL)
	{
		return NULL;
	}
	
	if (metadata->size > size)
	{
		memcpy(new_ptr, pointer, size);
	}
	else
	{
		memcpy(new_ptr, pointer, metadata->size);
	}
	
	kfree(pointer);
	
	return new_ptr;
}

void kfree(void* pointer)
{
	struct allocation_metadata* metadata = (void*) (pointer - PAGE_SIZE);
	pmm_free((void*) (metadata - PHYSICAL_MEMORY_OFFSET), metadata->pages + 1);
	debug("kmalloc: %d bytes freed!", metadata->size);
}
