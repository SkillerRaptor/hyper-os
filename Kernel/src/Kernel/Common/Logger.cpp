/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Serial.hpp>

namespace Kernel
{
	Logger::Level Logger::s_level{ Logger::Level::Debug };
	Spinlock Logger::s_spinlock{};

	void Logger::log(const char* format, ...)
	{
		s_spinlock.lock();

		va_list args;
		va_start(args, format);
		Logger::vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::vlog(const char* format, va_list args)
	{
		while (*format)
		{
			if (*format != '%')
			{
				Serial::write(*(format++));
				continue;
			}

			++format;

			size_t width = 0;
			while (Logger::is_digit(*format))
			{
				width = width * 10 + static_cast<size_t>(*(format++) - '0');
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
				auto c = static_cast<char>(va_arg(args, int32_t));
				Serial::write(c);
				break;
			}
			case 's':
			{
				auto string = va_arg(args, const char*);
				Serial::write(string);
				break;
			}
			default:
				Serial::write('%');
				break;
			}

			++format;
		}

		Serial::write('\n');
	}

	void Logger::info(const char* format, ...)
	{
		s_spinlock.lock();

		if (s_level > Logger::Level::Info)
		{
			s_spinlock.unlock();
			return;
		}

		Serial::write("\033[39m[\033[32m INFO \033[39m] ");

		va_list args;
		va_start(args, format);
		Logger::vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::warning(const char* format, ...)
	{
		s_spinlock.lock();

		if (s_level > Logger::Level::Warning)
		{
			s_spinlock.unlock();
			return;
		}

		Serial::write("\033[39m[\033[33m WARNING \033[39m] ");

		va_list args;
		va_start(args, format);
		Logger::vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::error(const char* format, ...)
	{
		s_spinlock.lock();

		if (s_level > Logger::Level::Error)
		{
			s_spinlock.unlock();
			return;
		}

		Serial::write("\033[39m[\033[31m ERROR \033[39m] ");

		va_list args;
		va_start(args, format);
		Logger::vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::debug(const char* format, ...)
	{
		s_spinlock.lock();

		if (s_level > Logger::Level::Debug)
		{
			s_spinlock.unlock();
			return;
		}

		Serial::write("\033[39m[\033[36m DEBUG \033[39m] ");

		va_list args;
		va_start(args, format);
		Logger::vlog(format, args);
		va_end(args);

		s_spinlock.unlock();
	}

	void Logger::set_level(Logger::Level level)
	{
		s_level = level;
	}

	Logger::Level Logger::level()
	{
		return s_level;
	}

	bool Logger::is_digit(char character)
	{
		return (character >= '0') && (character <= '9');
	}

	char* Logger::convert_to_string(uint64_t number, uint8_t base, size_t width, bool uppercase)
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
} // namespace Kernel
