/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel
{
	extern "C"
	{
		__attribute__((unused)) extern void* __dso_handle;

		__attribute__((used)) int __cxa_atexit(void (*destructor)(void*), void* object_ptr, void* dso_handle);
		__attribute__((used)) void __cxa_pure_virtual();
	}
} // namespace Kernel
