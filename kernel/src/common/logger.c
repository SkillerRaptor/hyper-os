/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "common/logger.h"

#include "arch/boot.h"
#include "lib/string.h"

#include <stdarg.h>
#include <stdbool.h>

static struct limine_terminal *s_terminal = NULL;
static limine_terminal_write s_write = NULL;

static void logger_write_string(const char *string)
{
	s_write(s_terminal, string, strlen(string));
}

static void logger_write_character(char character)
{
	s_write(s_terminal, &character, 1);
}

static bool logger_is_digit(char character)
{
	return (character >= '0') && (character <= '9');
}

static char *logger_convert_to_string(
	uint64_t number,
	uint8_t base,
	size_t min_width,
	bool uppercase,
	bool negative)
{
	static const char *s_lowercase_representation = "0123456789abcdef";
	static const char *s_uppercase_representation = "0123456789ABCDEF";
	static char buffer[50] = { 0 };

	const char *representation =
		uppercase ? s_uppercase_representation : s_lowercase_representation;

	char *character_ptr = &buffer[49];
	*character_ptr = '\0';

	size_t string_width = 0;
	do
	{
		*--character_ptr = representation[number % base];
		number /= base;

		++string_width;
	} while (number != 0);

	if (min_width != 0 && string_width < min_width)
	{
		size_t move_width = min_width - string_width;
		do
		{
			*--character_ptr = '0';
		} while (--move_width != 0);
	}

	if (negative)
	{
		*--character_ptr = '-';
	}

	return character_ptr;
}

static void logger_vlog(const char *format, va_list args)
{
	while (*format)
	{
		if (*format != '%')
		{
			logger_write_character(*(format++));
			continue;
		}

		++format;

		size_t width = 0;
		while (logger_is_digit(*format))
		{
			width *= 10;
			width += (size_t) (*(format++) - '0');
		}

		switch (*format)
		{
		case 'd':
		case 'i':
		{
			int64_t i = va_arg(args, int64_t);
			logger_write_string(logger_convert_to_string(i, 10, width, false, i < 0));
			break;
		}
		case 'u':
		{
			const uint64_t i = va_arg(args, uint64_t);
			logger_write_string(logger_convert_to_string(i, 10, width, false, false));
			break;
		}
		case 'o':
		{
			const uint64_t i = va_arg(args, uint64_t);
			logger_write_string(logger_convert_to_string(i, 8, width, false, false));
			break;
		}
		case 'x':
		{
			const uint64_t i = va_arg(args, uint64_t);
			logger_write_string(logger_convert_to_string(i, 16, width, false, false));
			break;
		}
		case 'X':
		{
			const uint64_t i = va_arg(args, uint64_t);
			logger_write_string(logger_convert_to_string(i, 16, width, true, false));
			break;
		}
		case 'c':
		{
			const char character = (char) va_arg(args, int32_t);
			logger_write_character(character);
			break;
		}
		case 's':
		{
			const char *string = va_arg(args, const char *);
			logger_write_string(string);
			break;
		}
		default:
			logger_write_character('%');
			break;
		}

		++format;
	}

	logger_write_character('\n');
}

void logger_init()
{
	struct limine_terminal_response *terminal_response = boot_get_terminal();
	if (terminal_response == NULL)
	{
		return;
	}

	if (terminal_response->terminal_count == 0)
	{
		return;
	}

	s_terminal = terminal_response->terminals[0];
	s_write = terminal_response->write;
}

void logger_info(const char *format, ...)
{
	logger_write_string("info: ");

	va_list args;
	va_start(args, format);

	logger_vlog(format, args);

	va_end(args);
}

void logger_warning(const char *format, ...)
{
	logger_write_string("warning: ");

	va_list args;
	va_start(args, format);

	logger_vlog(format, args);

	va_end(args);
}

void logger_error(const char *format, ...)
{
	logger_write_string("error: ");

	va_list args;
	va_start(args, format);

	logger_vlog(format, args);

	va_end(args);
}

void logger_debug(const char *format, ...)
{
	logger_write_string("debug: ");

	va_list args;
	va_start(args, format);

	logger_vlog(format, args);

	va_end(args);
}
