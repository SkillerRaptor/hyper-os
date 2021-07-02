/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <cstdlib>
#include <new>

void operator delete(void* ptr) noexcept
{
	std::free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept
{
	std::free(ptr);
}

[[nodiscard]] void* operator new[](std::size_t size)
{
	return std::malloc(size);
}

void operator delete[](void* ptr) noexcept
{
	std::free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept
{
	std::free(ptr);
}

[[nodiscard]] void* operator new(std::size_t, void* ptr) noexcept
{
	return ptr;
}

[[nodiscard]] void* operator new[](std::size_t, void* ptr) noexcept
{
	return ptr;
}

void operator delete(void*, void*) noexcept
{
}

void operator delete[](void*, void*) noexcept
{
}
