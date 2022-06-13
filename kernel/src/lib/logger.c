/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/logger.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/string.h"
#include "scheduling/spinlock.h"

#include <stdarg.h>
#include <stdbool.h>

#define FONT_COLOR_RED "\033[30;31m"
#define FONT_COLOR_GREEN "\033[30;32m"
#define FONT_COLOR_YELLOW "\033[30;33m"
#define FONT_COLOR_CYAN "\033[30;36m"

#define FONT_RESET "\033[0m"

static limine_terminal_write s_write = NULL;
static struct limine_terminal *s_terminal = NULL;
static struct spinlock s_lock = { 0 };

static void logger_vlog(const char *format, va_list args);
static void logger_write_string(const char *string);

void logger_init()
{
	struct limine_terminal_response *terminal_response = boot_get_terminal();
	assert(terminal_response != NULL);
	assert(terminal_response->terminal_count != 0);

	s_terminal = terminal_response->terminals[0];
	s_write = terminal_response->write;

	logger_info("Logger: Initialized");
}

void logger_info(const char *format, ...)
{
	spinlock_lock(&s_lock);

	logger_write_string(FONT_COLOR_GREEN "info" FONT_RESET ": ");

	va_list args;
	va_start(args, format);
	logger_vlog(format, args);
	va_end(args);

	spinlock_unlock(&s_lock);
}

void logger_warning(const char *format, ...)
{
	spinlock_lock(&s_lock);

	logger_write_string(FONT_COLOR_YELLOW "warning" FONT_RESET ": ");

	va_list args;
	va_start(args, format);
	logger_vlog(format, args);
	va_end(args);

	spinlock_unlock(&s_lock);
}

void logger_error(const char *format, ...)
{
	spinlock_lock(&s_lock);

	logger_write_string(FONT_COLOR_RED "error" FONT_RESET ": ");

	va_list args;
	va_start(args, format);
	logger_vlog(format, args);
	va_end(args);

	spinlock_unlock(&s_lock);
}

void logger_debug(const char *format, ...)
{
#ifndef NDEBUG
	spinlock_lock(&s_lock);

	logger_write_string(FONT_COLOR_CYAN "debug" FONT_RESET ": ");

	va_list args;
	va_start(args, format);
	logger_vlog(format, args);
	va_end(args);

	spinlock_unlock(&s_lock);
#endif
}

static void logger_write_character(char character)
{
	s_write(s_terminal, &character, 1);
}

static void logger_write_string(const char *string)
{
	s_write(s_terminal, string, strlen(string));
}

static char *logger_convert_to_string(
	uint64_t number,
	uint8_t base,
	size_t min_width,
	bool uppercase,
	bool negative)
{
	static char buffer[50] = { 0 };

	const char *representation =
		uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

	char *ptr = &buffer[49];
	*ptr = '\0';

	size_t string_width = 0;
	do
	{
		*--ptr = representation[number % base];
		number /= base;

		++string_width;
	} while (number != 0);

	if (min_width != 0 && string_width < min_width)
	{
		size_t move_width = min_width - string_width;
		do
		{
			*--ptr = '0';
		} while (--move_width != 0);
	}

	if (negative)
	{
		*--ptr = '-';
	}

	return ptr;
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
		while (isdigit(*format))
		{
			width *= 10;
			width += (size_t) (*(format++) - '0');
		}

		switch (*format)
		{
		case 'd':
		case 'i':
		{
			const int64_t i = va_arg(args, int64_t);
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
