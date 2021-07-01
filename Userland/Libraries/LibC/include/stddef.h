/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDDEF_H_
#define HYPEROS_LIBC_STDDEF_H_

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#if defined(__x86_64__)
typedef uint64_t size_t;
typedef int64_t ssize_t;
typedef int64_t ptrdiff_t;
typedef int64_t intptr_t;
#elif defined(__i386__)
typedef unsigned int size_t;
typedef int ssize_t;
typedef int ptrdiff_t;
typedef int intptr_t;
#endif

#ifndef NULL
#	define NULL ((void*) 0)
#endif

__END_DECLS

#endif // HYPEROS_LIBC_STDDEF_H_
