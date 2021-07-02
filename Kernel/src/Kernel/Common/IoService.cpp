/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/IoService.hpp>

namespace Kernel
{
	void IoService::outb(uint16_t port, uint8_t value)
	{
		__asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
	}

	uint8_t IoService::inb(uint16_t port)
	{
		uint8_t return_value = 0;

		__asm__ __volatile__("inb %1, %0" : "=a"(return_value) : "Nd"(port));

		return return_value;
	}

	void IoService::outw(uint16_t port, uint16_t value)
	{
		__asm__ __volatile__("outw %0, %1" : : "a"(value), "Nd"(port));
	}

	uint16_t IoService::inw(uint16_t port)
	{
		uint16_t return_value = 0;

		__asm__ __volatile__("inw %1, %0" : "=a"(return_value) : "Nd"(port));

		return return_value;
	}

	void IoService::wait()
	{
		IoService::outb(0x80, 0x00);
	}
} // namespace Kernel
