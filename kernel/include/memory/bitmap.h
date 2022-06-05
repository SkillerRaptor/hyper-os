/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct bitmap
{
	uint8_t *data;
	size_t size;
};

void bitmap_fill(struct bitmap *bitmap, uint8_t value);

void bitmap_set(struct bitmap *bitmap, size_t index, bool value);
bool bitmap_get(struct bitmap *bitmap, size_t index);
