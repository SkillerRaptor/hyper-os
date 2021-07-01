/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

static FILE std_streams[3];
FILE* stdin = &std_streams[0];
FILE* stdout = &std_streams[1];
FILE* stderr = &std_streams[2];

FILE* fopen(const char* file, const char* mode)
{
	// TODO: Implement fopen
	return NULL;
}

int fclose(FILE* stream)
{
	// TODO: Implement fclose
	return 0;
}

int fprintf(FILE* stream, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vfprintf(stream, format, args);
	va_end(args);
	
	return ret;
}

int printf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	
	return ret;
}

int sprintf(char* buffer, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vsprintf(buffer, format, args);
	va_end(args);
	
	return ret;
}

int snprintf(char* buffer, size_t buffer_size, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vsnprintf(buffer, buffer_size, format, args);
	va_end(args);
	
	return ret;
}

int vfprintf(FILE* stream, const char* format, va_list args)
{
	// TODO: Implement vfprintf
	return 0;
}

int vprintf(const char* format, va_list args)
{
	// TODO: Implement vprintf
	return 0;
}

int vsprintf(char* buffer, const char* format, va_list args)
{
	// TODO: Implement vsprintf
	return 0;
}

int vsnprintf(char* buffer, size_t buffer_size, const char* format, va_list args)
{
	// TODO: Implement vsnprintf
	return 0;
}