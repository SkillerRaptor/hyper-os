#pragma once

#include <LibC/sys/cdefs.h>
#include <LibC/sys/types.h>
#include <LibC/stdlib.h>
#include <LibC/stdarg.h>
#include <LibC/string.h>

#if defined(__is_libk)
#include "../../Kernel/Core/Terminal.h"
#endif

__BEGIN_DECLS

#ifndef EOF
#define EOF (-1)
#endif

int printf(const char* fmt, ...);
bool print(const char* str, size_t num);
int putchar(int character);
int puts(const char* str);

__END_DECLS