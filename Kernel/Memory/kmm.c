#include <Kernel/Memory/kmm.h>

#include <string.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/pmm.h>

#include <AK/logger.h>

typedef struct
{
	size_t pages;
	size_t size;
} heapheader_t;

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

void* kmalloc(size_t size)
{
	size_t page_count = (size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	info("page_count: %d", page_count);
	
	void* ptr = (uint8_t*)pmm_callocate_pages(page_count + 1);
	info("PTR: %s", to_string((uintptr_t) ptr));
	
	if (!ptr)
	{
		return NULL;
	}
	
	ptr += PHYSICAL_MEMORY_OFFSET;
	info("Hex: %s", to_string((uintptr_t) ptr));
	info("PTR: %s", to_string((uintptr_t) ptr));
	
	heapheader_t* metadata = ptr;
	ptr += PAGE_SIZE;
	info("metadata: %s", to_string((uintptr_t) metadata));
	info("PTR: %s", to_string((uintptr_t) ptr));
	
	metadata->pages = page_count;
	metadata->size = size;
	
	return ptr;
}

void* kcalloc(size_t num, size_t size)
{
	void* ptr = kmalloc(num * size);
	memset(ptr, 0, num * size);
	return ptr;
}

void* krealloc(void* ptr, size_t size)
{
	if (!ptr)
		return kmalloc(size);
	
	heapheader_t* metadata = ptr - PAGE_SIZE;
	
	size_t current_size = (metadata->size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	size_t new_size = (size + (PAGE_SIZE - 1)) / PAGE_SIZE;
	if (current_size == new_size)
	{
		metadata->size = new_size;
		return ptr;
	}
	
	void* new_ptr = kmalloc(new_size);
	if (new_ptr == NULL)
		return NULL;
	
	if (metadata->size > new_size)
		memcpy(new_ptr, ptr, new_size);
	else
		memcpy(new_ptr, ptr, metadata->size);
	
	kfree(ptr);
	
	return new_ptr;
}

void kfree(void* ptr)
{
	heapheader_t* metadata = ptr - PAGE_SIZE;
	pmm_free_pages((void*)metadata - PHYSICAL_MEMORY_OFFSET, metadata->pages + 1);
}