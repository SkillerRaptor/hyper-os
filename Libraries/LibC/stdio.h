#pragma once

#include <LibC/stdlib.h>
#include <LibC/stdarg.h>
#include <LibC/string.h>
#include <LibC/sys/cdefs.h>
#include <LibC/sys/types.h>

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