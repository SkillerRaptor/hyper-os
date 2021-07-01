/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDARG_H_
#define HYPEROS_LIBC_STDARG_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef __builtin_va_list va_list;

#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v, l)

__END_DECLS

#endif // HYPEROS_LIBC_STDARG_H_
