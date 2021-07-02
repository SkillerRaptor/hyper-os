/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Memory.hpp>

namespace Kernel
{
	void* memset(void* destination, int value, size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			*(reinterpret_cast<uint8_t*>(destination) + i) = value;
		}
		
		return destination;
	}

	void* memcpy(void* destination, const void* source, size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			*(reinterpret_cast<uint8_t*>(destination) + i) = *(reinterpret_cast<const uint8_t*>(source) + i);
		}

		return destination;
	}
} // namespace Kernel
