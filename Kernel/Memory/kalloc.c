#include "kalloc.h"

#include "memory.h"
#include "pmm.h"

#include <utilities/builtins.h>
#include <utilities/logger.h>
#include <utilities/math.h>

struct allocation_metadata
{
	size_t pages;
	size_t size;
};

void* kmalloc(size_t size)
{
	size_t page_count = DIV_ROUNDUP(size, PAGE_SIZE);
	
	void *ptr = (char*) pmm_calloc(page_count + 1);
	
	if (ptr == NULL)
	{
		return NULL;
	}
	
	ptr += PHYSICAL_MEMORY_OFFSET;
	
	struct allocation_metadata* metadata = ptr;
	ptr += PAGE_SIZE;
	
	metadata->pages = page_count;
	metadata->size = size;
	
	debug("kmalloc: %d bytes allocated!", size);
	
	return ptr;
}

void* kcalloc(size_t num, size_t size)
{
	void* ptr = kmalloc(num * size);
	memset(ptr, 0x0, num * size);
	return ptr;
}

void* krealloc(void* ptr, size_t size)
{
	if (ptr == NULL)
	{
		return kmalloc(size);
	}
	
	struct allocation_metadata* metadata = ptr - PAGE_SIZE;
	
	if(DIV_ROUNDUP(metadata->size, PAGE_SIZE) == DIV_ROUNDUP(size, PAGE_SIZE))
	{
		metadata->size = size;
		return ptr;
	}
	
	void* new_ptr = kmalloc(size);
	if (new_ptr == NULL)
	{
		return NULL;
	}
	
	if (metadata->size > size)
	{
		memcpy(new_ptr, ptr, size);
	}
	else
	{
		memcpy(new_ptr, ptr, metadata->size);
	}
	
	kfree(ptr);
	
	return new_ptr;
}

void kfree(void* ptr)
{
	struct allocation_metadata* metadata = ptr - PAGE_SIZE;
	pmm_free((void*) metadata - PHYSICAL_MEMORY_OFFSET, metadata->pages + 1);
	debug("kmalloc: %d bytes freed!", metadata->size);
}
