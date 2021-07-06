/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Synchronization/Spinlock.hpp>
#include <stdarg.h>
#include <stdint.h>

namespace Kernel
{
	class Logger
	{
	public:
		enum class Level
		{
			Info,
			Warning,
			Error,
			Debug
		};
	
	public:
		static void log(const char* format, ...);
		static void vlog(const char* format, va_list args);
		
		static void info(const char* format, ...);
		static void warning(const char* format, ...);
		static void error(const char* format, ...);
		static void debug(const char* format, ...);
	
	private:
		static char* convert_to_string(uint64_t number, int64_t base, uint64_t width, bool uppercase);
		
		static bool is_digit(char c);
		
	private:
		static Spinlock s_spinlock;
	};
} // namespace Kernel
