/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_SETJMP_H_
#define HYPEROS_LIBC_SETJMP_H_

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

struct __jmp_buf_128
{
	uint64_t _part[2];
};

typedef struct __jmp_buf_128 jmp_buf[16];

#ifndef setjmp
#	define setjmp __setjmp
#endif

int __setjmp(jmp_buf environment);
void longjmp(jmp_buf environment, int value);

__END_DECLS

#endif // HYPEROS_LIBC_SETJMP_H_
