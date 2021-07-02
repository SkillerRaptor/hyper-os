/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace Kernel
{
	extern "C"
	{
		static constexpr const size_t s_atexit_max_functions = 128;

		extern void* __dso_handle;

		struct AtexitFunctionEntry
		{
			void (*destructor)(void*);
			void* object_ptr;
			void* dso_handle;
		};

		int __cxa_atexit(void (*destructor)(void*), void* object_ptr, void* dso_handle);
	}
} // namespace Kernel
