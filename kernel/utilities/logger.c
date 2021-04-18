#include "logger.h"

#include <utilities/serial.h>

#include <stdarg.h>

enum
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
};

static void log_string(int status, const char* format, va_list args);
static char* string_convert(unsigned int number, int base);

void info(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	
	log_string(INFO, format, args);
	
	va_end(args);
}

void warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	
	log_string(WARNING, format, args);
	
	va_end(args);
}

void error(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	
	log_string(ERROR, format, args);
	
	va_end(args);
}

void debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	
	log_string(DEBUG, format, args);
	
	va_end(args);
}

static void log_string(int status, const char* format, va_list args)
{
	const char* string = "";
	
	switch (status)
	{
	case INFO:
		string = COLOR_FOREGROUND_RESET "[" COLOR_FOREGROUND_GREEN " INFO " COLOR_FOREGROUND_RESET "] ";
		break;
	case WARNING:
		string = COLOR_FOREGROUND_RESET "[" COLOR_FOREGROUND_ORANGE " WARNING " COLOR_FOREGROUND_RESET "] ";
		break;
	case ERROR:
		string = COLOR_FOREGROUND_RESET "[" COLOR_FOREGROUND_RED " ERROR " COLOR_FOREGROUND_RESET "] ";
		break;
	case DEBUG:
		string = COLOR_FOREGROUND_RESET "[" COLOR_FOREGROUND_CYAN " DEBUG " COLOR_FOREGROUND_RESET "] ";
		break;
	}
	
	serial_write_string(string);
	
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 'c':
			{
				int i = va_arg(args, int);
				serial_write(i);
				break;
			}
			case 'd':
			{
				int i = va_arg(args, int);
				if (i < 0)
				{
					i = -i;
					serial_write('-');
				}
				serial_write_string(string_convert(i, 10));
				break;
			}
			case 'o':
			{
				unsigned int i = va_arg(args, unsigned int);
				serial_write_string(string_convert(i, 8));
				break;
			}
			case 's':
			{
				char* str = va_arg(args, char*);
				serial_write_string(str);
				break;
			}
			case 'x':
			{
				unsigned int i = va_arg(args, unsigned int);
				serial_write_string("0x");
				serial_write_string(string_convert(i, 16));
				break;
			}
			default:
				serial_write('%');
				break;
			}
		}
		else
		{
			serial_write(*format);
		}
		
		format++;
	}
	
	serial_write('\n');
}

static char* string_convert(unsigned int number, int base)
{
	static char representation[] = "0123456789ABCDEF";
	
	static char buffer[50];
	char* ptr;
	
	ptr = &buffer[49];
	*ptr = '\0';
	
	do
	{
		*--ptr = representation[number % base];
		number /= base;
	} while (number != 0);
	
	return ptr;
}