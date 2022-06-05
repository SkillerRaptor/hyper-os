/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/string.h"

size_t strlen(const char *string)
{
	if (string == NULL)
	{
		return 0;
	}

	size_t i = 0;
	while (string[i] != '\0')
	{
		++i;
	}

	return i;
}

int strncmp(const char *string1, const char *string2, size_t count)
{
	for (size_t i = 0; i < count; ++i)
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
