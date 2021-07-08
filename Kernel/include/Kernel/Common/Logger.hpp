/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Synchronization/Spinlock.hpp>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

namespace Kernel
{
	class Logger
	{
	public:
		enum class Level : uint8_t
		{
			Debug = 0,
			Info,
			Warning,
			Error
		};

	private:
		enum class ConvertFlags : uint8_t
		{
			None = 0,
			Uppercase = 1 << 0,
			Negative = 1 << 1
		};
	
	public:
		static void info(const char* format, ...);
		static void warning(const char* format, ...);
		static void error(const char* format, ...);
		static void debug(const char* format, ...);
		
		static void set_level(Level level);
		static Level level();
	
	private:
		static void vlog(const char* format, va_list args);
		
		static bool is_digit(char character);
		static char* convert_to_string(uint64_t number, uint8_t base, size_t min_width, ConvertFlags flags);
		
		friend bool operator&(const ConvertFlags& left, const ConvertFlags& right);
		friend ConvertFlags operator|(const ConvertFlags& left, const ConvertFlags& right);
		friend ConvertFlags operator|=(ConvertFlags& left, const ConvertFlags& right);
		
	private:
		static Level s_level;
		static Spinlock s_spinlock;
	};
} // namespace Kernel
