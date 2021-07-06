/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Memory.hpp>
#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Serial.hpp>
#include <stddef.h>

namespace Kernel
{
	Spinlock Logger::s_spinlock{};

	void Logger::log(const char* format, ...)
	{
		s_spinlock.lock();

		va_list args;
		va_start(args, format);
		vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::vlog(const char* format, va_list args)
	{
		while (*format)
		{
			if (*format == '%')
			{
				++format;

				uint64_t width = 0;
				while (is_digit(*format))
				{
					width = width * 10 + static_cast<uint64_t>(*format - '0');
					++format;
				}

				switch (*format)
				{
				case 'd':
				case 'i':
				{
					auto i = va_arg(args, int32_t);
					if (i < 0)
					{
						i = -i;
						Serial::write('-');
					}
					Serial::write(Logger::convert_to_string(i, 10, width, false));
					break;
				}
				case 'u':
				{
					auto i = va_arg(args, uint64_t);
					Serial::write(Logger::convert_to_string(i, 10, width, false));
					break;
				}
				case 'o':
				{
					auto i = va_arg(args, uint64_t);
					Serial::write(Logger::convert_to_string(i, 8, width, false));
					break;
				}
				case 'x':
				{
					auto i = va_arg(args, uint64_t);
					Serial::write(Logger::convert_to_string(i, 16, width, false));
					break;
				}
				case 'X':
				{
					auto i = va_arg(args, uint64_t);
					Serial::write(Logger::convert_to_string(i, 16, width, true));
					break;
				}
				case 'c':
				{
					auto c = static_cast<char>(va_arg(args, int));
					Serial::write(c);
					break;
				}
				case 's':
				{
					auto str = va_arg(args, char*);
					Serial::write(str);
					break;
				}
				default:
					Serial::write('%');
					break;
				}
			}
			else
			{
				Serial::write(*format);
			}

			++format;
		}

		Serial::write('\n');
	}

	void Logger::info(const char* format, ...)
	{
		s_spinlock.lock();

		Serial::write("\033[39m[\033[32m INFO \033[39m] ");

		va_list args;
		va_start(args, format);
		vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::warning(const char* format, ...)
	{
		s_spinlock.lock();

		Serial::write("\033[39m[\033[33m WARNING \033[39m] ");

		va_list args;
		va_start(args, format);
		vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::error(const char* format, ...)
	{
		s_spinlock.lock();

		Serial::write("\033[39m[\033[31m ERROR \033[39m] ");

		va_list args;
		va_start(args, format);
		vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::debug(const char* format, ...)
	{
		s_spinlock.lock();

		Serial::write("\033[39m[\033[36m DEBUG \033[39m] ");

		va_list args;
		va_start(args, format);
		vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	char* Logger::convert_to_string(uint64_t number, int64_t base, uint64_t width, bool uppercase)
	{
		static constexpr const char* lowercase_representation = "0123456789abcdef";
		static constexpr const char* uppercase_representation = "0123456789ABCDEF";

		static char buffer[50] = { 0 };
		char* ptr = &buffer[49];
		*ptr = '\0';

		size_t string_width = 0;

		do
		{
			*--ptr = (uppercase ? uppercase_representation : lowercase_representation)[number % base];
			number /= base;
			++string_width;
		} while (number != 0);

		if (width > 0 && string_width < width)
		{
			size_t move_width = width - string_width;
			do
			{
				*--ptr = '0';
			} while (--move_width != 0);
		}

		return ptr;
	}

	bool Logger::is_digit(char c)
	{
		return (c >= '0') && (c <= '9');
	}
} // namespace Kernel
