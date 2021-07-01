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

#if defined(__x86_64__)
struct __jmp_buf_128
{
	uint64_t _part[2];
};

#	define _jmp_buf_length 16
#	define _jmp_buf_type struct __jmp_buf_128
#elif defined(__i386__)
#	define _jmp_buf_length 16
#	define _jmp_buf_type int
#endif

typedef _jmp_buf_type jmp_buf[_jmp_buf_length];

#ifndef setjmp
#	define setjmp __setjmp
#endif

int __setjmp(jmp_buf environment);
void longjmp(jmp_buf environment, int value);

__END_DECLS

#endif // HYPEROS_LIBC_SETJMP_H_
