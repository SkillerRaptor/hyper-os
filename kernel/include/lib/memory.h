/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

#define BYTE_SIZE 8
#define PAGE_SIZE 4096

void *memcpy(void *destination, const void *source, size_t count);
void *memset(void *destination, int value, size_t count);
