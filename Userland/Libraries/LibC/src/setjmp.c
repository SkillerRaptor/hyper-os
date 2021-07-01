/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <setjmp.h>

int __setjmp(jmp_buf environment)
{
	// TODO: Implement __setjmp in asm
	return 0;
}

void longjmp(jmp_buf environment, int value)
{
	// TODO: Implement longjmp in asm
}