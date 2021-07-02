/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stivale2.h>
#include <stddef.h>

namespace Kernel
{
	struct PageMap
	{
		uintptr_t top_level;
		//Spinlock spinlock;
	};
	
	class VirtualMemoryManager
	{
	public:
		static void initialize(stivale2_mmap_entry* memory_map, size_t memory_map_entries);
		
		static PageMap* create_page_map();
		static void switch_page_map(PageMap* page_map);
		static bool map_page(PageMap* page_map, uintptr_t physical_address, uintptr_t virtual_address, uintptr_t flags);
	
		static PageMap* kernel_page_map();
		
	private:
		static uintptr_t* get_next_level(uintptr_t* current_level, size_t entry, bool allocate);
		static uintptr_t* virtual2pte(PageMap* page_map, uintptr_t virtual_address, bool allocate);
		
	private:
		static PageMap* s_kernel_page_map;
	};
}
