/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>

void abort(void)
{
	// TODO: Implement abort
	
	while (1)
	{
		asm volatile("cli");
		asm volatile("hlt");
	}
}