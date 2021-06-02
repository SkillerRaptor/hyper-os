#include <AK/Math.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <AK/Memory.hpp>

namespace Kernel
{
	uintptr_t PhysicalMemoryManager::s_highest_page{ 0 };
	size_t PhysicalMemoryManager::s_last_used_index{ 0 };
	AK::Bitmap PhysicalMemoryManager::s_bitmap{};
	
	void PhysicalMemoryManager::initialize(stivale2_mmap_entry* memory_map, size_t memory_map_entries)
	{
		for (size_t i = 0; i < memory_map_entries; ++i)
		{
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
		
		size_t bitmap_size = AK::Math::div_round_up(s_highest_page, AK::s_page_size) / AK::s_byte_size;
		for (size_t i = 0; i < memory_map_entries; ++i)
		{
			if (memory_map[i].type != STIVALE2_MMAP_USABLE)
			{
				continue;
			}
			
			if (memory_map[i].length >= bitmap_size)
			{
				s_bitmap.set_data(reinterpret_cast<uint8_t*>(memory_map[i].base + AK::s_physical_memory_offset));
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
			
			for (uintptr_t j{ 0 }; j < memory_map[i].length; j += AK::s_page_size)
			{
				s_bitmap.reset((memory_map[i].base + j) / AK::s_page_size);
			}
		}
	}
	
	void* PhysicalMemoryManager::allocate(size_t num)
	{
		size_t limit = s_last_used_index;
		void* ptr = internal_allocate(num, s_highest_page / AK::s_page_size);
		if (ptr == nullptr)
		{
			s_last_used_index = 0;
			ptr = internal_allocate(num, limit);
		}
		
		return ptr;
	}
	
	void* PhysicalMemoryManager::callocate(size_t num)
	{
		auto* ptr = reinterpret_cast<uint8_t*>(allocate(num));
		if (ptr == nullptr)
		{
			return nullptr;
		}
		
		auto* address = reinterpret_cast<uint64_t*>(ptr + AK::s_physical_memory_offset);
		for (size_t i = 0; i < num * (AK::s_page_size / sizeof(uint64_t)); i++)
		{
			address[i] = 0x00;
		}
		
		return ptr;
	}
	
	void PhysicalMemoryManager::free(void* ptr, size_t num)
	{
		auto page = reinterpret_cast<size_t>(ptr) / AK::s_page_size;
		for (size_t i = page; i < page + num; i++)
		{
			s_bitmap.reset(i);
		}
	}
	
	void* PhysicalMemoryManager::internal_allocate(size_t num, size_t limit)
	{
		size_t p = 0;
		
		while (s_last_used_index < limit)
		{
			if (!s_bitmap.test(s_last_used_index++))
			{
				p = 0;
				continue;
			}
			
			if (++p == num)
			{
				size_t page = s_last_used_index - num;
				for (size_t i = page; i < s_last_used_index; i++)
				{
					s_bitmap.set(i);
				}
				return reinterpret_cast<void*>(page * AK::s_page_size);
			}
		}
		
		return nullptr;
	}
}
