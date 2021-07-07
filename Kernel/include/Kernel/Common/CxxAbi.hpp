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
