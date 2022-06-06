/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

void pmm_init(void);

void *pmm_alloc(size_t page_count);
void *pmm_calloc(size_t page_count);
void pmm_free(void *ptr, size_t page_count);

size_t pmm_get_memory_offset();
