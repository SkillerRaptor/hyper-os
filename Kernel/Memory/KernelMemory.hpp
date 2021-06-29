/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace Kernel
{
	void* malloc(size_t size);
	void* calloc(size_t num, size_t size);
	void* realloc(void* ptr, size_t size);
	void free(void* ptr);
}

void* operator new(size_t size);
void* operator new[](size_t size);
void* operator new(size_t size, void* ptr);
void* operator new[](size_t size, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);
void operator delete(void* ptr, size_t size);
void operator delete[](void* ptr, size_t size);
void operator delete(void* ptr, void* place);
void operator delete[](void* ptr, void* place);
