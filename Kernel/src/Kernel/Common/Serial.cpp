/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/IoService.hpp>
#include <Kernel/Common/Serial.hpp>
#include <stdint.h>

namespace Kernel::Serial
{
	static constexpr const uint16_t s_serial_port = 0x03F8;

	void initialize()
	{
		IoService::outb(s_serial_port + 1, 0x00);
		IoService::outb(s_serial_port + 3, 0x80);
		IoService::outb(s_serial_port + 0, 0x03);
		IoService::outb(s_serial_port + 1, 0x00);
		IoService::outb(s_serial_port + 3, 0x03);
		IoService::outb(s_serial_port + 2, 0xC7);
		IoService::outb(s_serial_port + 4, 0x0B);
		IoService::outb(s_serial_port + 4, 0x1E);
		IoService::outb(s_serial_port + 0, 0xAE);

		if (IoService::inb(s_serial_port + 0) != 0xAE)
		{
			return;
		}

		IoService::outb(s_serial_port + 4, 0x0F);
	}

	void write(char character)
	{
		__volatile__ uint64_t i_ = 0;
		while ((IoService::inb(s_serial_port + 5) & 0x20) == 0)
		{
			__asm__ __volatile__(
				""
				: "+g"(i_)
				:
				:);
		}

		IoService::outb(s_serial_port, character);
	}

	void write(const char* string)
	{
		while (*string)
		{
			write(*(string++));
		}
	}
} // namespace Kernel::Serial
