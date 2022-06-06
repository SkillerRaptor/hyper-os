/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

struct page_map
{
	uintptr_t top_level;
};

void vmm_init(void);

struct page_map *vmm_create_page_map();
void vmm_map_page(
	struct page_map *page_map,
	uintptr_t physical_address,
	uintptr_t virtual_address,
	uintptr_t flags);
void vmm_switch_page_map(struct page_map *page_map);
