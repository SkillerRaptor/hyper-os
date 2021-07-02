/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/String.hpp>

namespace Kernel
{
	int strncmp(const char* string1, const char* string2, size_t num)
	{
		for (size_t i = 0; i < num; ++i)
		{
			const char first_char = string1[i];
			const char second_char = string2[i];

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
} // namespace Kernel
