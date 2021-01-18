#include <LibC/stdio.h>

#include <LibC/ctype.h>
#include <LibC/string.h>

char* __int_str(intmax_t i, char b[], int base, bool plusSignIfNeeded, bool spaceSignIfNeeded,
	int paddingNo, bool justify, bool zeroPad)
{
	char digit[32] = { 0 };
	memset(digit, 0, 32);
	strcpy(digit, "0123456789");

	if (base == 16) {
		strcat(digit, "ABCDEF");
	}
	else if (base == 17) {
		strcat(digit, "abcdef");
		base = 16;
	}

	char* p = b;
	if (i < 0) {
		*p++ = '-';
		i *= -1;
	}
	else if (plusSignIfNeeded)
	{
		*p++ = '+';
	}
	else if (!plusSignIfNeeded && spaceSignIfNeeded)
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

	int padding = paddingNo - (int)strlen(b);
	if (padding < 0) padding = 0;

	if (justify)
	{
		while (padding--)
			if (zeroPad)
				b[strlen(b)] = '0';
			else
				b[strlen(b)] = ' ';
	}
	else
	{
		char a[256] = { 0 };
		while (padding--)
			if (zeroPad)
				a[strlen(a)] = '0';
			else
				a[strlen(a)] = ' ';
		strcat(a, b);
		strcpy(b, a);
	}

	return b;
}

void printChar(char c, int* ret)
{
	putchar(c);
	(*ret)++;
}

void printString(const char* c, int* ret)
{
	for (size_t i = 0; c[i]; ++i)
		printChar(c[i], ret);
}

int vprintf(const char* fmt, va_list parameters)
{
	int ret = 0;
	char stringBuffer[256] = { 0 };

	for (size_t i = 0; fmt[i]; ++i)
	{
		char specifier = '\0';
		char length = '\0';

		int lengthSpec = 0;
		int precSpec = 0;

		bool leftJustify = false;
		bool plusSign = false;
		bool spaceNoSign = false;
		bool zeroPad = false;

		int expo = 0;

		if (fmt[i] == '%')
		{
			i++;
			bool exitBreak = false;
			while (true)
			{
				switch (fmt[i])
				{
				case '-':
					leftJustify = true;
					i++;
					break;
				case '+':
					plusSign = true;
					i++;
					break;
				case ' ':
					spaceNoSign = true;
					i++;
					break;
				case '0':
					zeroPad = true;
					i++;
					break;
				default:
					exitBreak = true;
					break;
				}
				if (exitBreak) break;
			}

			while (isdigit(fmt[i]))
			{
				lengthSpec *= 10;
				lengthSpec += fmt[i] - 48;
				i++;
			}

			if (fmt[i] == '*')
			{
				lengthSpec = va_arg(parameters, int);
				i++;
			}

			if (fmt[i] == '.')
			{
				++i;
				while (isdigit(fmt[i]))
				{
					precSpec *= 10;
					precSpec += fmt[i] - 48;
					++i;
				}

				if (fmt[i] == '*')
				{
					precSpec = va_arg(parameters, int);
					++i;
				}
			}
			else
				precSpec = 6;

			if (fmt[i] == 'h' || fmt[i] == 'l' || fmt[i] == 'j' || fmt[i] == 'z' || fmt[i] == 't' || fmt[i] == 'L')
			{
				length = fmt[i];
				++i;
				if (fmt[i] == 'h')
					length = 'H';
				else if (fmt[i] == 'l')
				{
					length = 'q';
					++i;
				}
			}

			specifier = fmt[i];

			memset(stringBuffer, 0, 256);

			int base = 10;
			if (specifier == 'o')
			{
				base = 8;
				specifier = 'u';
				printString("0", &ret);
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
				printString("0x", &ret);

				switch (length)
				{
				case 0:
				{
					unsigned int integer = va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'H':
				{
					unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'h':
				{
					unsigned short int integer = va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'l':
				{
					unsigned long integer = va_arg(parameters, unsigned long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'q':
				{
					unsigned long long integer = va_arg(parameters, unsigned long long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'j':
				{
					uintmax_t integer = va_arg(parameters, uintmax_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'z':
				{
					size_t integer = va_arg(parameters, size_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 't':
				{
					ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				default:
					break;
				}
				break;
			case 'x':
				base = (base == 10) ? 17 : base;
				printString("0x", &ret);

				switch (length)
				{
				case 0:
				{
					unsigned int integer = va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'H':
				{
					unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'h':
				{
					unsigned short int integer = va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'l':
				{
					unsigned long integer = va_arg(parameters, unsigned long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'q':
				{
					unsigned long long integer = va_arg(parameters, unsigned long long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'j':
				{
					uintmax_t integer = va_arg(parameters, uintmax_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'z':
				{
					size_t integer = va_arg(parameters, size_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 't':
				{
					ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
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
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'H':
				{
					unsigned char integer = (unsigned char)va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'h':
				{
					unsigned short int integer = va_arg(parameters, unsigned int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'l':
				{
					unsigned long integer = va_arg(parameters, unsigned long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'q':
				{
					unsigned long long integer = va_arg(parameters, unsigned long long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'j':
				{
					uintmax_t integer = va_arg(parameters, uintmax_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'z':
				{
					size_t integer = va_arg(parameters, size_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 't':
				{
					ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
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
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'H':
				{
					signed char integer = (signed char)va_arg(parameters, int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'h':
				{
					short int integer = va_arg(parameters, int);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'l':
				{
					long integer = va_arg(parameters, long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'q':
				{
					long long integer = va_arg(parameters, long long);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'j':
				{
					intmax_t integer = va_arg(parameters, intmax_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 'z':
				{
					size_t integer = va_arg(parameters, size_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
					break;
				}
				case 't':
				{
					ptrdiff_t integer = va_arg(parameters, ptrdiff_t);
					__int_str(integer, stringBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
					printString(stringBuffer, &ret);
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
					printChar(va_arg(parameters, wint_t), &ret);
				else
					printChar(va_arg(parameters, int), &ret);

				break;
			}

			case 's':
			{
				printString(va_arg(parameters, char*), &ret);
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
				printString("e+", &ret);
			else if (specifier == 'E')
				printString("E+", &ret);

			if (specifier == 'e' || specifier == 'E') {
				__int_str(expo, stringBuffer, 10, false, false, 2, false, true);
				printString(stringBuffer, &ret);
			}
		}
		else
			printChar(fmt[i], &ret);
	}

	return ret;
}

__BEGIN_DECLS

/* Formatted input/output */
int printf(const char* fmt, ...)
{
	va_list parameters;
	va_start(parameters, fmt);
	int ret = vprintf(fmt, parameters);
	va_end(parameters);
	return ret;
}

/* Character input/output */
int putchar(int character)
{
#if defined(__is_libk)
	char c = (char)character;
	Terminal::Write(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif

	return character;
}

int puts(const char* str)
{
	return printf("%s\n", str);
}

__END_DECLS