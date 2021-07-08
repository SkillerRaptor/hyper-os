/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace Kernel
{
	class String
	{
	public:
		String() = default;
		String(const char* string);

	private:
		size_t m_size{ 0 };
		const char* m_buffer{ nullptr };
	};

	extern "C"
	{
		constexpr int strncmp(const char* left, const char* right, size_t num)
		{
			for (size_t i = 0; i < num; ++i)
			{
				const char first_char = left[i];
				const char second_char = right[i];

				if (first_char != second_char)
				{
					return first_char - second_char;
				}

				if (!first_char)
				{
					return 0;
				}
			}

			return 0;
		}

		constexpr size_t strlen(const char* string)
		{
			if (string == nullptr)
			{
				return 0;
			}

			size_t length = 0;

			while (*(string++))
			{
				++length;
			}

			return length;
		}
	}
} // namespace Kernel
