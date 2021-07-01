/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDIO_H_
#define HYPEROS_LIBC_STDIO_H_

#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

struct __FILE
{
	unsigned char _flag;
	unsigned char _file;
	// TODO: Implement __FILE
};

typedef struct __FILE FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

FILE* fopen(const char* file, const char* mode);
int fclose(FILE* stream);

int fprintf(FILE* stream, const char* format, ...);
int printf(const char* format, ...);
int sprintf(char* buffer, const char* format, ...);
int snprintf(char* buffer, size_t buffer_size, const char* format, ...);

int vfprintf(FILE* stream, const char* format, va_list args);
int vprintf(const char* format, va_list args);
int vsprintf(char* buffer, const char* format, va_list args);
int vsnprintf(char* buffer, size_t buffer_size, const char* format, va_list args);

__END_DECLS

#endif // HYPEROS_LIBC_STDIO_H_
