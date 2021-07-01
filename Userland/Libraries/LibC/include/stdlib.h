/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDLIB_H_
#define HYPEROS_LIBC_STDLIB_H_

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

__attribute__((__noreturn__)) void abort(void);

void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

__END_DECLS

#endif // HYPEROS_LIBC_STDLIB_H_
