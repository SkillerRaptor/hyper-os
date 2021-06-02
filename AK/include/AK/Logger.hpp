#pragma once

#include <AK/String.hpp>
#include <AK/StringView.hpp>
#include <stdarg.h>
#include <STDINT.h>

namespace AK
{
	// TODO: Implement formatting with templates
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
		static void log(Level level, const char* string, ...);
		static void vlog(Level level, const char* string, va_list args);
		
		static void info(const char* string, ...);
		static void warning(const char* string, ...);
		static void error(const char* string, ...);
		static void debug(const char* string, ...);
	
	private:
		static char* convert_string(uint32_t number, int32_t base);
	};
}
