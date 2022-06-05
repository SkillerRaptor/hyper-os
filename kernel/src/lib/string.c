/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/string.h"

size_t strlen(const char *string)
{
	size_t i = 0;
	while (string[i] != '\0')
	{
		++i;
	}

	return i;
}
