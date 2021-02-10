#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#if defined(__is_libk)
#include <Kernel/Core/Terminal.h>
#endif

__BEGIN_DECLS

#ifndef EOF
#define EOF (-1)
#endif

/* Formatted input/output */
int printf(const char* fmt, ...);

/* Character input/output */
int putchar(int character);
int puts(const char* str);

__END_DECLS