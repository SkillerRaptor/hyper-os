/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/CxxAbi.hpp>
#include <stddef.h>

namespace Kernel
{
	struct AtexitFunctionEntry
	{
		void (*destructor)(void*);
		void* object_ptr;
		void* dso_handle;
	};

	static constexpr const size_t s_atexit_max_functions = 128;

	static size_t s_atexit_function_count = 0;
	static AtexitFunctionEntry s_atexit_functions[s_atexit_max_functions] = {};

	void* __dso_handle = nullptr;

	int __cxa_atexit(void (*destructor)(void*), void* object_ptr, void* dso_handle)
	{
		if (s_atexit_function_count >= s_atexit_max_functions)
		{
			return -1;
		}

		s_atexit_functions[s_atexit_function_count].destructor = destructor;
		s_atexit_functions[s_atexit_function_count].object_ptr = object_ptr;
		s_atexit_functions[s_atexit_function_count].dso_handle = dso_handle;
		++s_atexit_function_count;

		return 0;
	}

	void __cxa_pure_virtual()
	{
		// TODO: Assert / Panic here!
	}
} // namespace Kernel
