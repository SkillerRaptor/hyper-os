/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <AK/Bitmap.hpp>
#include <AK/Spinlock.hpp>
#include <Kernel/Boot/Stivale.hpp>
#include <stddef.h>

namespace Kernel
{
	class PhysicalMemoryManager
	{
	public:
		static void initialize(stivale2_mmap_entry* memory_map, size_t memory_map_entries);
		
		static void* allocate(size_t num);
		static void* callocate(size_t num);
		
		static void free(void* ptr, size_t num);
	
	private:
		static void* internal_allocate(size_t num, size_t limit);
		
	private:
		static uintptr_t s_highest_page;
		static size_t s_last_used_index;
		static AK::Bitmap s_bitmap;
		static AK::Spinlock s_spinlock;
	};
}
