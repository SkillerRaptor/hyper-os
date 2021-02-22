#include <stdio.h>

#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <AK/serial.h>

static void print_internal_char(char c, int* ret)
{
	putchar(c);
	*ret += 1;
}

static void print_internal_string(const char* c, int* ret)
{
	for (size_t i = 0; c[i]; ++i)
		print_internal_char(c[i], ret);
}

static char* internal_string_format(intmax_t i, char b[], int base, bool plus_sign, bool space_sign, int padding_offset, bool justify, bool zero)
{
	char digit[32] = { 0 };
	memset(digit, 0, 32);
	strcpy(digit, "0123456789");

	if (base == 16)
	{
		strcat(digit, "ABCDEF");
	}
	else if (base == 17)
	{
		strcat(digit, "abcdef");
		base = 16;
	}

	char* p = b;
	if (i < 0)
	{
		*p++ = '-';
		i *= -1;
	}
	else if (plus_sign)
	{
		*p++ = '+';
	}
	else if (!plus_sign && space_sign)
	{
		*p++ = ' ';
	}

	intmax_t shifter = i;
	do
	{
		++p;
		shifter = shifter / base;
	} while (shifter);

	*p = '\0';
	do
	{
		*--p = digit[i % base];
		i = i / base;
	} while (i);

	int padding = padding_offset - (int)strlen(b);
	if (padding < 0) padding = 0;

	if (justify)
	{
		while (padding--)
		{
			if (zero)
				b[strlen(b)] = '0';
			else
				b[strlen(b)] = ' ';
		}
	}
	else
	{
		char a[256] = { 0 };
		while (padding--)
		{
			if (zero)
				a[strlen(a)] = '0';
			else
				a[strlen(a)] = ' ';
		}
		strcat(a, b);
		strcpy(b, a);
	}

	return b;
}

int vprintf(const char* fmt, va_list parameters)
{
	int ret = 0;
	char string_buffer[256] = { 0 };

	for (size_t i = 0; fmt[i]; ++i)
	{
		if (fmt[i] != '%')
		{
			putchar(fmt[i]);
			++ret;
			continue;
		}

		++i;

		bool left_justify = false;
		bool plus_sign = false;
		bool space_no_sign = false;
		bool zero_pad = false;

		bool exit_break = false;
		while (true)
		{
			switch (fmt[i])
			{
			case '-':
				left_justify = true;
				++i;
				break;
			case '+':
				plus_sign = true;
				++i;
				break;
			case ' ':
				space_no_sign = true;
				++i;
				break;
			case '0':
				zero_pad = true;
				++i;
				break;
			default:
				exit_break = true;
				break;
			}

			if (exit_break)
				break;
		}

		size_t length_spec = 0;

		while (isdigit(fmt[i]))
		{
			length_spec *= 10;
			length_spec += fmt[i] - 48;
			++i;
		}

		if (fmt[i] == '*')
		{
			length_spec = va_arg(parameters, int);
				++i;
		}

		size_t prec_spec = 0;

		if (fmt[i] == '.')
		{
			++i;
			while (isdigit(fmt[i]))
			{
				prec_spec *= 10;
				prec_spec += fmt[i] - 48;
				++i;
			}

			if (fmt[i] == '*')
			{
				prec_spec = va_arg(parameters, int);
				++i;
			}
		}
		else
		{
			prec_spec = 6;
		}

		char specifier = '\0';
		char length = '\0';

		if (fmt[i] == 'h' || fmt[i] == 'l' || fmt[i] == 'j' || fmt[i] == 'z' || fmt[i] == 't' || fmt[i] == 'L')
		{
			length = fmt[i];
			++i;
			if (fmt[i] == 'h')
			{
				length = 'H';
			}
			else if (fmt[i] == 'l')
			{
				length = 'q';
				++i;
			}
		}

		specifier = fmt[i];

		memset(string_buffer, 0, 256);

		int base = 10;
		if (specifier == 'o')
		{
			base = 8;
			specifier = 'u';
			print_internal_string("0", &ret);
		}

		if (specifier == 'p')
		{
			base = 16;
			length = 'z';
			specifier = 'u';
		}

		switch (specifier)
		{
		case 'X':
			base = 16;
			base = (base == 10) ? 17 : base;
			print_internal_string("0x", &ret);

			switch (length)
			{
			case 0:
			{
				unsigned int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'H':
			{
				unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'h':
			{
				unsigned short int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'l':
			{
				unsigned long integer = va_arg(parameters, unsigned long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'q':
			{
				unsigned long long integer = va_arg(parameters, unsigned long long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'j':
			{
				uintmax_t integer = va_arg(parameters, uintmax_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'z':
			{
				size_t integer = va_arg(parameters, size_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 't':
			{
				ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			default:
				break;
			}
			break;
		case 'x':
			base = (base == 10) ? 17 : base;
			print_internal_string("0x", &ret);

			switch (length)
			{
			case 0:
			{
				unsigned int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'H':
			{
				unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'h':
			{
				unsigned short int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'l':
			{
				unsigned long integer = va_arg(parameters, unsigned long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'q':
			{
				unsigned long long integer = va_arg(parameters, unsigned long long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'j':
			{
				uintmax_t integer = va_arg(parameters, uintmax_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'z':
			{
				size_t integer = va_arg(parameters, size_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 't':
			{
				ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			default:
				break;
			}
			break;
		case 'u':
		{
			switch (length)
			{
			case 0:
			{
				unsigned int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'H':
			{
				unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'h':
			{
				unsigned short int integer = va_arg(parameters, unsigned int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'l':
			{
				unsigned long integer = va_arg(parameters, unsigned long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'q':
			{
				unsigned long long integer = va_arg(parameters, unsigned long long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'j':
			{
				uintmax_t integer = va_arg(parameters, uintmax_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'z':
			{
				size_t integer = va_arg(parameters, size_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 't':
			{
				ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			default:
				break;
			}
			break;
		}

		case 'd': case 'i':
		{
			switch (length)
			{
			case 0:
			{
				int integer = va_arg(parameters, int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'H':
			{
				signed char integer = (signed char)va_arg(parameters, int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'h':
			{
				short int integer = va_arg(parameters, int);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'l':
			{
				long integer = va_arg(parameters, long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'q':
			{
				long long integer = va_arg(parameters, long long);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'j':
			{
				intmax_t integer = va_arg(parameters, intmax_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 'z':
			{
				size_t integer = va_arg(parameters, size_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			case 't':
			{
				ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
				internal_string_format(integer, string_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
				print_internal_string(string_buffer, &ret);
				break;
			}
			default:
				break;
			}
			break;
		}

		case 'c':
		{
			if (length == 'l')
				print_internal_char(va_arg(parameters, wint_t), &ret);
			else
				print_internal_char(va_arg(parameters, int), &ret);
			break;
		}

		case 's':
		{
			print_internal_string(va_arg(parameters, char*), &ret);
			break;
		}

		case 'n':
		{
			switch (length)
			{
			case 'H':
				*(va_arg(parameters, signed char*)) = ret;
				break;
			case 'h':
				*(va_arg(parameters, short int*)) = ret;
				break;

			case 0:
			{
				int* a = va_arg(parameters, int*);
				*a = ret;
				break;
			}

			case 'l':
				*(va_arg(parameters, long*)) = ret;
				break;
			case 'q':
				*(va_arg(parameters, long long*)) = ret;
				break;
			case 'j':
				*(va_arg(parameters, intmax_t*)) = ret;
				break;
			case 'z':
				*(va_arg(parameters, size_t*)) = ret;
				break;
			case 't':
				*(va_arg(parameters, ptrdiff_t*)) = ret;
				break;
			default:
				break;
			}
			break;
		}

		default:
			break;
		}

		if (specifier == 'e')
			print_internal_string("e+", &ret);
		else if (specifier == 'E')
			print_internal_string("E+", &ret);

		if (specifier == 'e' || specifier == 'E') {
			internal_string_format(0, string_buffer, 10, false, false, 2, false, true);
			print_internal_string(string_buffer, &ret);
		}
	}

	return ret;
}

int printf(const char* fmt, ...)
{
	va_list parameters;
	va_start(parameters, fmt);
	int ret = vprintf(fmt, parameters);
	va_end(parameters);
	return ret;
}

int putchar(int character)
{
	// TODO: Implement stdio and the write system call.
	serial_write(character);
	return character;
}

int puts(const char* str)
{
	return printf("%s\n", str);
}