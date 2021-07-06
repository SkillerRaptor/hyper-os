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

		for (size_t i = 0; i < count; ++i)
		{
			dest[i] = static_cast<uint8_t>(value);
		}

		return destination;
	}

	void* memcpy(void* destination, const void* source, size_t count)
	{
		auto* dest = reinterpret_cast<uint8_t*>(destination);
		const auto* src = reinterpret_cast<const uint8_t*>(source);

		for (size_t i = 0; i < count; ++i)
		{
			dest[i] = src[i];
		}

		return dest;
	}

	void* memmove(void* destination, const void* source, size_t count)
	{
		auto* dest = reinterpret_cast<uint8_t*>(destination);
		const auto* src = reinterpret_cast<const uint8_t*>(source);

		if (src > dest)
		{
			for (size_t i = 0; i < count; ++i)
			{
				dest[i] = src[i];
			}
		}
		else if (src < dest)
		{
			for (size_t i = count; i > 0; --i)
			{
				dest[i - 1] = src[i - 1];
			}
		}

		return dest;
	}
} // namespace Kernel
