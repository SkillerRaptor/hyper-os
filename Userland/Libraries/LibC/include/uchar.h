/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_UCHAR_H_
#define HYPEROS_LIBC_UCHAR_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

struct __mbstate
{
	unsigned long _char;
	unsigned short _byte;
	unsigned short _state;
};

typedef struct __mbstate mbstate_t;

__END_DECLS

#endif // HYPEROS_LIBC_UCHAR_H_
