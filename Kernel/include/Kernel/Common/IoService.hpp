/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	class IoService
	{
	public:
		static void outb(uint16_t port, uint8_t value);
		static uint8_t inb(uint16_t port);

		static void outw(uint16_t port, uint16_t value);
		static uint16_t inw(uint16_t port);

		static void wait();
	};
} // namespace Kernel
