/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <AK/String.hpp>
#include <AK/StringView.hpp>

namespace AK
{
	class Serial
	{
	private:
		static constexpr const uint16_t s_serial_port{ 0x03F8 };
		
	public:
		static void initialize();
		
		static bool transmit_empty();
		
		static void write(char c);
		static void write(const char* string);
		static void write(const StringView& string);
		static void write(const String& string);
	};
}
