#include <LibC/stdio.h>

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

bool print(const char* str, size_t num)
{
    const unsigned char* bytes = (const unsigned char*)str;
    for (size_t i = 0; i < num; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}

int printf(const char* fmt, ...)
{
    va_list parameters;
    va_start(parameters, fmt);

    int written = 0;

    while (*fmt != '\0')
    {
        size_t maxrem = INT32_MAX - written;

        if (fmt[0] != '%' || fmt[1] == '%')
        {
            if (fmt[0] == '%')
                fmt++;
            size_t amount = 1;
            while (fmt[amount] && fmt[amount] != '%')
                amount++;
            if (maxrem < amount)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(fmt, amount))
                return -1;
            fmt += amount;
            written += amount;
            continue;
        }

        const char* fmt_begun_at = fmt++;

        if (*fmt == 'c')
        {
            fmt++;
            char c = (char)va_arg(parameters, int);
            if (!maxrem)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        }
        else if (*fmt == 's')
        {
            fmt++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        }
        else
        {
            fmt = fmt_begun_at;
            size_t len = strlen(fmt);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(fmt, len))
                return -1;
            written += len;
            fmt += len;
        }
    }

    va_end(parameters);
    return written;
}