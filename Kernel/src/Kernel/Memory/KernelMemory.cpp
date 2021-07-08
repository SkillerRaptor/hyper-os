/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Math.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Memory/KernelMemory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <stdint.h>

namespace Kernel::Memory
{
	struct AllocationHeader
	{
		size_t page_count;
		size_t size;
	};

	void* malloc(size_t size)
	{
		size_t page_count = Math::div_round_up(size, Memory::s_page_size);

		auto* ptr = reinterpret_cast<uint8_t*>(PhysicalMemoryManager::callocate(page_count + 1));
		if (ptr == nullptr)
		{
			return nullptr;
		}

		ptr = ptr + Memory::s_physical_memory_offset;

		auto* header = reinterpret_cast<AllocationHeader*>(ptr);
		ptr = ptr + Memory::s_page_size;

		header->page_count = page_count;
		header->size = size;

		return ptr;
	}

	void* calloc(size_t num, size_t size)
	{
		void* ptr = malloc(num * size);
		Memory::memset(ptr, 0x00, num * size);
		return ptr;
	}

	void* realloc(void* ptr, size_t size)
	{
		if (ptr == nullptr)
		{
			return malloc(size);
		}

		auto* header_address = reinterpret_cast<uint8_t*>(ptr) - Memory::s_page_size;
		auto* header = reinterpret_cast<AllocationHeader*>(header_address);

		if (Math::div_round_up(header->size, Memory::s_page_size) == Math::div_round_up(size, Memory::s_page_size))
		{
			header->size = size;
			return ptr;
		}

		void* new_pointer = malloc(size);
		if (new_pointer == nullptr)
		{
			return nullptr;
		}
		
		Memory::memcpy(new_pointer, ptr, (header->size > size) ? size : header->size);
		free(ptr);

		return new_pointer;
	}

	void free(void* ptr)
	{
		auto* header_address = reinterpret_cast<uint8_t*>(ptr) - Memory::s_page_size;
		auto* header = reinterpret_cast<AllocationHeader*>(header_address);

		size_t page_count = header->page_count + 1;
		PhysicalMemoryManager::free(reinterpret_cast<void*>(header_address - Memory::s_physical_memory_offset), page_count);
	}
} // namespace Kernel

[[nodiscard]] void* operator new(size_t size)
{
	return Kernel::Memory::malloc(size);
}

void operator delete(void* ptr) noexcept
{
	Kernel::Memory::free(ptr);
}

void operator delete(void* ptr, size_t) noexcept
{
	Kernel::Memory::free(ptr);
}

[[nodiscard]] void* operator new[](size_t size)
{
	return Kernel::Memory::malloc(size);
}

void operator delete[](void* ptr) noexcept
{
	Kernel::Memory::free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept
{
	Kernel::Memory::free(ptr);
}

[[nodiscard]] void* operator new(size_t, void* ptr) noexcept
{
	return ptr;
}

[[nodiscard]] void* operator new[](size_t, void* ptr) noexcept
{
	return ptr;
}

void operator delete(void*, void*) noexcept
{
}

void operator delete[](void*, void*) noexcept
{
}
