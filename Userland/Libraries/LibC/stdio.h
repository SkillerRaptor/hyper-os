#ifndef HYPEROS_USERLAND_LIBARIRES_LIBC_STDIO_H_
#define HYPEROS_USERLAND_LIBARIRES_LIBC_STDIO_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef EOF
#define EOF (-1)
#endif

int vprintf(const char* fmt, va_list parameters);

int printf(const char* fmt, ...);

int putchar(int character);
int puts(const char* str);

#endif