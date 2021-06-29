/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Kernel
{
	class IDT
	{
	private:
		enum HandlerType : uint8_t
		{
			Present = 1 << 7,
			InterruptGate = 1 << 1 | 1 << 2 | 1 << 3,
			TrapGate = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3
		};
		
		struct Entry
		{
			uint16_t offset_low;
			uint16_t selector;
			uint8_t ist;
			uint8_t attributes;
			uint16_t offset_middle;
			uint32_t offset_high;
			uint32_t zero;
		} __attribute__((packed));
		
		struct Pointer
		{
			uint16_t size;
			uint64_t address;
		} __attribute__((packed));
	
	public:
		static void initialize();
		static void reload();
		
		static void register_handler(size_t index, uint8_t flags, uintptr_t handler);
		static void register_interrupt_handler(size_t index, uintptr_t handler);
		static void register_trap_handler(size_t index, uintptr_t handler);
	
	private:
		static Entry s_entries[256];
	};
}
