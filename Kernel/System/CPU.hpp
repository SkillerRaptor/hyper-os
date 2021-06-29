/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Boot/Stivale.hpp>
#include <stdint.h>

namespace Kernel
{
	class CPU
	{
	public:
		struct LocalData
		{
			uint64_t stack;
			uint64_t lapic_id;
		};
		
	public:
		__attribute__((noreturn)) static void initialize();
		
		static uint64_t read_timestamp();
		static void invalidate_page(void* m);
		
		static void write_msr(uint64_t msr, uint64_t value);
		static uint64_t read_msr(uint64_t msr);
		
		static void write_user_fs(uintptr_t value);
		static uintptr_t user_fs();
		
		static void write_user_gs(uintptr_t value);
		static uintptr_t user_gs();
		
		static void write_kernel_gs(uintptr_t value);
		static uintptr_t kernel_gs();
		
		static LocalData current_cpu();
	
	private:
		static uint64_t s_current_cpu;
	};
}
