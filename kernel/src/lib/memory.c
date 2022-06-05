/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/memory.h"

#include <stdint.h>

void *memset(void *destination, int value, size_t count)
{
	uint8_t *destination_ptr = (uint8_t *) destination;

	for (size_t i = 0; i < count; i++)
	{
		destination_ptr[i] = (uint8_t) value;
	}

	return destination;
}
