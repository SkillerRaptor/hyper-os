/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/memory.h"

#include <stdint.h>

void *memcpy(void *destination, const void *source, size_t count)
{
	uint8_t *destination_ptr = (uint8_t *) destination;
	const uint8_t *source_ptr = (uint8_t *) source;

	for (size_t i = 0; i < count; ++i)
	{
		destination_ptr[i] = source_ptr[i];
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t count)
{
	uint8_t *destination_ptr = (uint8_t *) destination;
	const uint8_t *source_ptr = (uint8_t *) source;

	if (source_ptr > destination_ptr)
	{
		for (size_t i = 0; i < count; ++i)
		{
			destination_ptr[i] = source_ptr[i];
		}

		return destination;
	}

	for (size_t i = count; i > 0; --i)
	{
		destination_ptr[i - 1] = source_ptr[i - 1];
	}

	return destination;
}

void *memset(void *destination, int value, size_t count)
{
	uint8_t *destination_ptr = (uint8_t *) destination;

	for (size_t i = 0; i < count; i++)
	{
		destination_ptr[i] = (uint8_t) value;
	}

	return destination;
}
