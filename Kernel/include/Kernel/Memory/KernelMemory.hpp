/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace Kernel::Memory
{
	void* malloc(size_t size);
	void* calloc(size_t num, size_t size);
	void* realloc(void* ptr, size_t size);
	void free(void* ptr);
} // namespace Kernel::Memory

[[nodiscard]] void* operator new(size_t size);

void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, size_t) noexcept;

[[nodiscard]] void* operator new[](size_t size);

void operator delete[](void* ptr) noexcept;
void operator delete[](void* ptr, size_t) noexcept;

[[nodiscard]] void* operator new(size_t, void* ptr) noexcept;
[[nodiscard]] void* operator new[](size_t, void* ptr) noexcept;
void operator delete(void*, void*) noexcept;
void operator delete[](void*, void*) noexcept;
