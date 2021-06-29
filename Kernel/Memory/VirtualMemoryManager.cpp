/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <AK/Logger.hpp>
#include <AK/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>

namespace Kernel
{
	PageMap* VirtualMemoryManager::s_kernel_page_map{ nullptr };
	
	void VirtualMemoryManager::initialize(stivale2_mmap_entry* memory_map, size_t memory_map_entries)
	{
		AK::Logger::info("VMM: Initializing...");
		
		s_kernel_page_map = VirtualMemoryManager::create_page_map();
		
		for (uintptr_t p = 0; p < 0x100000000; p += AK::s_page_size)
		{
			VirtualMemoryManager::map_page(s_kernel_page_map, p, p + AK::s_physical_memory_offset, 0x03);
		}
		
		for (uintptr_t p = 0; p < 0x80000000; p += AK::s_page_size)
		{
			VirtualMemoryManager::map_page(s_kernel_page_map, p, p + AK::s_kernel_base_address, 0x03);
		}
		
		for (size_t i = 0; i < memory_map_entries; i++)
		{
			for (uintptr_t p = 0; p < memory_map[i].length; p += AK::s_page_size)
			{
				VirtualMemoryManager::map_page(s_kernel_page_map, p, p + AK::s_physical_memory_offset, 0x03);
			}
		}
		
		VirtualMemoryManager::switch_page_map(s_kernel_page_map);
		
		AK::Logger::info("VMM: Initializing finished!");
	}
	
	PageMap* VirtualMemoryManager::create_page_map()
	{
		auto* page_map = new PageMap();
		page_map->top_level = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(1));
		if (s_kernel_page_map != nullptr)
		{
			uintptr_t* top_level{ reinterpret_cast<uintptr_t*>(page_map->top_level + AK::s_physical_memory_offset) };
			uintptr_t* kernel_top_level{ reinterpret_cast<uintptr_t*>(page_map->top_level + AK::s_physical_memory_offset) };
			for (size_t i = 256; i < 512; i++)
			{
				top_level[i] = kernel_top_level[i];
			}
		}
		return page_map;
	}
	
	void VirtualMemoryManager::switch_page_map(PageMap* page_map)
	{
		asm volatile (
		"mov %%cr3, %0"
		:
		: "r" (page_map->top_level)
		: "memory"
		);
	}
	
	bool VirtualMemoryManager::map_page(PageMap* page_map, uintptr_t physical_address, uintptr_t virtual_address, uintptr_t flags)
	{
		page_map->spinlock.lock();
		
		uintptr_t* pte = virtual2pte(page_map, virtual_address, true);
		if (pte == nullptr)
		{
			page_map->spinlock.unlock();
			return false;
		}
		
		*pte = physical_address | flags;
		
		page_map->spinlock.unlock();
		
		return true;
	}
	
	uintptr_t* VirtualMemoryManager::get_next_level(uintptr_t* current_level, size_t entry, bool allocate)
	{
		
		if (current_level[entry] & 0x1)
		{
			uintptr_t level_entry = current_level[entry] & ~((uintptr_t) 0xFFF);
			return reinterpret_cast<uintptr_t*>(level_entry + AK::s_physical_memory_offset);
		}
		
		if (!allocate)
		{
			return nullptr;
		}
		
		auto next_level = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(1));
		if (next_level == 0)
		{
			return nullptr;
		}
		
		current_level[entry] = next_level | 0b111;
		
		uintptr_t level_entry = current_level[entry] & ~((uintptr_t) 0xFFF);
		return reinterpret_cast<uintptr_t*>(level_entry + AK::s_physical_memory_offset);
	}
	
	uintptr_t* VirtualMemoryManager::virtual2pte(PageMap* page_map, uintptr_t virtualAddress, bool allocate)
	{
		uintptr_t pml4_entry = (virtualAddress & ((uintptr_t) 0x1FF << 39)) >> 39;
		uintptr_t pml3_entry = (virtualAddress & ((uintptr_t) 0x1FF << 30)) >> 30;
		uintptr_t pml2_entry = (virtualAddress & ((uintptr_t) 0x1FF << 21)) >> 21;
		uintptr_t pml1_entry = (virtualAddress & ((uintptr_t) 0x1FF << 12)) >> 12;
		
		auto* pml4 = reinterpret_cast<uintptr_t*>(page_map->top_level + AK::s_physical_memory_offset);
		
		uintptr_t* pml3 = get_next_level(pml4, pml4_entry, allocate);
		if (pml3 == nullptr)
		{
			return nullptr;
		}
		
		uintptr_t* pml2 = get_next_level(pml3, pml3_entry, allocate);
		if (pml2 == nullptr)
		{
			return nullptr;
		}
		
		uintptr_t* pml1 = get_next_level(pml2, pml2_entry, allocate);
		if (pml1 == nullptr)
		{
			return nullptr;
		}
		
		return &pml1[pml1_entry];
	}
	
	PageMap* VirtualMemoryManager::kernel_page_map()
	{
		return s_kernel_page_map;
	}
}
