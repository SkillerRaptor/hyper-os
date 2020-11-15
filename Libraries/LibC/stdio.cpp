#include <LibC/stdio.h>

static constexpr const char* HexDigits = "0123456789abcdef";

int printHex(int number, uint8_t fields)
{
    int ret = 0;
    uint8_t shrCount = fields * 4;
    while (shrCount)
    {
        shrCount -= 4;
        putchar(HexDigits[(number >> shrCount) & 0x0F]);
        ++ret;
    }
    return ret;
}

char printNumber(int number)
{
    uint32_t divisor = 1000000000;
    char ch;
    char padding = 1;
    int ret = 0;

    for (;;) {
        ch = '0' + (number / divisor);
        number %= divisor;

        if (ch != '0')
            padding = 0;

        if (!padding || divisor == 1) {
            putchar(ch);
            ++ret;
        }

        if (divisor == 1)
            break;
        divisor /= 10;
    }

    return ret;
}

int printSignedNumber(int number)
{
    if (number < 0)
    {
        putchar('-');
        return printNumber(0 - number) + 1;
    }
    return printNumber(number);
}

int printfInternal(char* str, const char* fmt, va_list parameters)
{
    const char* ptr;
    int ret = 0;

    for (ptr = fmt; *ptr; ++ptr)
        if (*ptr == '%' && *(ptr + 1))
        {
            ++ptr;
            switch (*ptr)
            {
            case 's':
            {
                const char* stringParameters = va_arg(parameters, const char*);
                //ASSERT(sp != nullptr);
                if (!stringParameters) 
                {
                    putchar('(');
                    putchar('n');
                    putchar('u');
                    putchar('l');
                    putchar('l');
                    putchar(')');
                    ret += 6;
                }
                else 
                {
                    for (; *stringParameters; ++stringParameters) 
                    {
                        putchar(*stringParameters);
                        ++ret;
                    }
                }
                break;
            }
            case 'd':
                ret += printSignedNumber(va_arg(parameters, int));
                break;
            case 'u':
                ret += printNumber(va_arg(parameters, int));
                break;
            case 'x':
                ret += printHex(va_arg(parameters, int), 8);
                break;
            case 'w':
                ret += printHex(va_arg(parameters, int), 4);
                break;
            case 'b':
                ret += printHex(va_arg(parameters, int), 2);
                break;
            case 'c':
                putchar(va_arg(parameters, int));
                ++ret;
                break;
            case 'p':
                putchar('0');
                putchar('x');
                ret += 2;
                ret += printHex(va_arg(parameters, int), 8);
                break;
            }
        }
        else
        {
            putchar(*ptr);
            ++ret;
        }

    return ret;
}

__BEGIN_DECLS

/* Formatted input/output */
int printf(const char* fmt, ...)
{
    va_list parameters;
    va_start(parameters, fmt);
    int ret = printfInternal(nullptr, fmt, parameters);
    va_end(parameters);
    return ret;
}

int sprintf(char* str, const char* fmt, ...)
{
    va_list parameters;
    va_start(parameters, fmt);
    int ret = printfInternal(str, fmt, parameters);
    str[ret] = '\0';
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