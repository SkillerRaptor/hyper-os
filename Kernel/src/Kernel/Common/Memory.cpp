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
		auto* dest = reinterpret_cast<uint8_t*>(destination);
		
		__volatile__ uint64_t i_ = 0;
		for (size_t i = 0; i < count; ++i)
		{
			__asm__ __volatile__(
				""
				: "+g" (i_)
				:
				:
			);
			
			dest[i] = static_cast<uint8_t>(value);
		}

		return destination;
	}

	void* memcpy(void* destination, const void* source, size_t count)
	{
		auto* dest = reinterpret_cast<uint8_t*>(destination);
		const auto* src = reinterpret_cast<const uint8_t*>(source);
		
		__volatile__ uint64_t i_ = 0;
		for (size_t i = 0; i < count; ++i)
		{
			__asm__ __volatile__(
				""
				: "+g" (i_)
				:
				:
			);
			
			dest[i] = src[i];
		}

		return dest;
	}

	void* memmove(void* destination, const void* source, size_t count)
	{
		auto* dest = reinterpret_cast<uint8_t*>(destination);
		const auto* src = reinterpret_cast<const uint8_t*>(source);
		
		__volatile__ uint64_t i_ = 0;
		if (src > dest)
		{
			for (size_t i = 0; i < count; ++i)
			{
				__asm__ __volatile__(
					""
					: "+g" (i_)
					:
					:
				);
				dest[i] = src[i];
			}
		}
		else if (src < dest)
		{
			for (size_t i = count; i > 0; --i)
			{
				__asm__ __volatile__(
					""
					: "+g" (i_)
					:
					:
				);
				dest[i - 1] = src[i - 1];
			}
		}

		return dest;
	}
} // namespace Kernel
