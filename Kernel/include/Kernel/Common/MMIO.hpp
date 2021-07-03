/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	class MMIO
	{
	public:
		static void outb(void* address, uint8_t value);
		static uint8_t inb(void* address);
		
		static void outw(void* address, uint16_t value);
		static uint16_t inw(void* address);
		
		static void outd(void* address, uint32_t value);
		static uint32_t ind(void* address);
		
		static void outq(void* address, uint64_t value);
		static uint64_t inq(void* address);
	};
} // namespace Kernel
