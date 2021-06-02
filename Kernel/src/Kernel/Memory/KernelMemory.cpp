#include <AK/Math.hpp>
#include <AK/Memory.hpp>
#include <Kernel/Memory/KernelMemory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/System/Stdlib.hpp>
#include <stdint.h>

namespace Kernel
{
	struct AllocationHeader
	{
		size_t page_count;
		size_t size;
	};
	
	void* malloc(size_t size)
	{
		size_t page_count = AK::Math::div_round_up(size, AK::s_page_size);
		
		auto* ptr = reinterpret_cast<uint8_t*>(PhysicalMemoryManager::callocate(page_count + 1));
		if (ptr == nullptr)
		{
			return nullptr;
		}
		
		ptr = ptr + AK::s_physical_memory_offset;
		
		auto* header = reinterpret_cast<AllocationHeader*>(ptr);
		ptr = ptr + AK::s_page_size;
		
		header->page_count = page_count;
		header->size = size;
		
		return ptr;
	}
	
	void* calloc(size_t num, size_t size)
	{
		void* ptr{ malloc(num * size) };
		memset(ptr, 0x00, num * size);
		return ptr;
	}
	
	void* realloc(void* ptr, size_t size)
	{
		if (ptr == nullptr)
		{
			return malloc(size);
		}
		
		auto* header_address = reinterpret_cast<uint8_t*>(ptr) - AK::s_page_size;
		auto* header{ reinterpret_cast<AllocationHeader*>(header_address) };
		
		if (AK::Math::div_round_up(header->size, AK::s_page_size) == AK::Math::div_round_up(size, AK::s_page_size))
		{
			header->size = size;
			return ptr;
		}
		
		void* new_pointer = malloc(size);
		if (new_pointer == nullptr)
		{
			return nullptr;
		}
		
		memcpy(new_pointer, ptr, (header->size > size) ? size : header->size);
		free(ptr);
		
		return new_pointer;
	}
	
	void free(void* ptr)
	{
		auto* header_address = reinterpret_cast<uint8_t*>(ptr) - AK::s_page_size;
		auto* header = reinterpret_cast<AllocationHeader*>(header_address);
		
		size_t page_count = header->page_count + 1;
		PhysicalMemoryManager::free(reinterpret_cast<void*>(header_address - AK::s_physical_memory_offset), page_count);
	}
}

void* operator new(size_t size)
{
	return Kernel::malloc(size);
}

void* operator new[](size_t size)
{
	return Kernel::malloc(size);
}

void* operator new(size_t, void* ptr)
{
	return ptr;
}

void* operator new[](size_t, void* ptr)
{
	return ptr;
}

void operator delete(void* ptr)
{
	Kernel::free(ptr);
}

void operator delete[](void* ptr)
{
	Kernel::free(ptr);
}

void operator delete(void* ptr, size_t)
{
	Kernel::free(ptr);
}

void operator delete[](void* ptr, size_t)
{
	Kernel::free(ptr);
}

void operator delete(void*, void*)
{
}

void operator delete[](void*, void*)
{
}
