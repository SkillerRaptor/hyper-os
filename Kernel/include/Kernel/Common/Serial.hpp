/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel
{
	class Serial
	{
	private:
		static constexpr const uint16_t s_serial_port{ 0x03F8 };

	public:
		static void initialize();

		static void write(char character);
		static void write(const char* string);

	private:
		static bool transmit_empty();
	};
} // namespace Kernel
