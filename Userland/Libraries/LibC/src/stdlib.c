/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <string.h>

void abort(void)
{
	// TODO: Implement abort

	while (1)
	{
		asm volatile("cli");
		asm volatile("hlt");
	}
}

void* malloc(size_t size)
{
	// TODO: Implement malloc
}

void* calloc(size_t num, size_t size)
{
	void* ptr = malloc(num * size);
	memset(ptr, 0x00, num * size);
	return ptr;
}

void* realloc(void* ptr, size_t size)
{
	// TODO: Implement realloc
}

void free(void* ptr)
{
	// TODO: Implement free
}