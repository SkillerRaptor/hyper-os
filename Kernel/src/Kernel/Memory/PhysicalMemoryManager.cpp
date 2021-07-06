/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Math.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>

namespace Kernel
{
	uintptr_t PhysicalMemoryManager::s_highest_page{ 0 };
	size_t PhysicalMemoryManager::s_last_used_index{ 0 };
	Bitmap PhysicalMemoryManager::s_bitmap{};
	Spinlock PhysicalMemoryManager::s_spinlock{};

	void PhysicalMemoryManager::initialize(stivale2_mmap_entry* memory_map, size_t memory_map_entries)
	{
		Logger::info("PMM: Initializing...");

		for (size_t i = 0; i < memory_map_entries; ++i)
		{
			Logger::debug(
				"[Entry %d] [0x%X - 0x%X]: Size: 0x%X - Type: 0x%X",
				i,
				memory_map[i].base,
				memory_map[i].base + memory_map[i].length,
				memory_map[i].length,
				memory_map[i].type);

			if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			{
				continue;
			}

			uintptr_t top_page = memory_map[i].base + memory_map[i].length;
			if (top_page > s_highest_page)
			{
				s_highest_page = top_page;
			}
		}

		size_t bitmap_size = Math::div_round_up(s_highest_page, s_page_size) / s_byte_size;
		for (size_t i = 0; i < memory_map_entries; ++i)
		{
			if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			{
				continue;
			}

			if (memory_map[i].length >= bitmap_size)
			{
				s_bitmap.set_data(reinterpret_cast<uint8_t*>(memory_map[i].base + s_physical_memory_offset));
				s_bitmap.set_size(bitmap_size);

				s_bitmap.set();

				memory_map[i].length -= bitmap_size;
				memory_map[i].base += bitmap_size;

				break;
			}
		}

		for (size_t i = 0; i < memory_map_entries; ++i)
		{
			if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			{
				continue;
			}

			for (uintptr_t j = 0; j < memory_map[i].length; j += s_page_size)
			{
				s_bitmap.reset((memory_map[i].base + j) / s_page_size);
			}
		}

		Logger::info("PMM: Initializing finished!");
	}

	void* PhysicalMemoryManager::allocate(size_t num)
	{
		s_spinlock.lock();

		size_t limit = s_last_used_index;
		void* ptr = internal_allocate(num, s_highest_page / s_page_size);
		if (ptr == nullptr)
		{
			s_last_used_index = 0;
			ptr = internal_allocate(num, limit);
		}

		s_spinlock.unlock();

		return ptr;
	}

	void* PhysicalMemoryManager::callocate(size_t num)
	{
		auto* ptr = reinterpret_cast<uint8_t*>(allocate(num));
		if (ptr == nullptr)
		{
			return nullptr;
		}

		auto* address = reinterpret_cast<uint64_t*>(ptr + s_physical_memory_offset);
		for (size_t i = 0; i < num * (s_page_size / sizeof(uint64_t)); i++)
		{
			address[i] = 0x00;
		}

		return ptr;
	}

	void PhysicalMemoryManager::free(void* ptr, size_t num)
	{
		s_spinlock.lock();

		size_t page = reinterpret_cast<size_t>(ptr) / s_page_size;
		for (size_t i = page; i < page + num; i++)
		{
			s_bitmap.reset(i);
		}

		s_spinlock.unlock();
	}

	void* PhysicalMemoryManager::internal_allocate(size_t num, size_t limit)
	{
		size_t p = 0;

		while (s_last_used_index < limit)
		{
			if (!s_bitmap.test(s_last_used_index++))
			{
				if (++p == num)
				{
					size_t page = s_last_used_index - num;
					for (size_t i = page; i < s_last_used_index; i++)
					{
						s_bitmap.set(i);
					}
					return reinterpret_cast<void*>(page * s_page_size);
				}
			}
			else
			{
				p = 0;
			}
		}

		return nullptr;
	}
} // namespace Kernel
