/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "memory/bitmap.h"

#include "lib/memory.h"

void bitmap_fill(struct bitmap *bitmap, uint8_t value)
{
	memset(bitmap->data, value, bitmap->size);
}

void bitmap_set(struct bitmap *bitmap, size_t index, bool value)
{
	const size_t byte = index / 8;
	const size_t bit = index % 8;

	if (!value)
	{
		bitmap->data[byte] &= ~(1 << (bit));
		return;
	}

	bitmap->data[byte] |= (1 << (bit));
}

bool bitmap_get(struct bitmap *bitmap, size_t index)
{
	const size_t byte = index / 8;
	const size_t bit = index % 8;

	return bitmap->data[byte] & (1 << (bit));
}
