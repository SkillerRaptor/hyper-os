/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STRING_H_
#define HYPEROS_LIBC_STRING_H_

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t length);

size_t strlen(const char* string);

int memcmp(const void* source1, const void* source2, size_t count);
void* memset(void* destination, int value, size_t count);
void* memcpy(void* destination, const void* source, size_t count);
void* memmove(void* destination, const void* source, size_t count);

__END_DECLS

#endif // HYPEROS_LIBC_STRING_H_
