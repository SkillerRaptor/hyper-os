/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/boot.h"

static volatile struct limine_hhdm_request s_hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0,
};

static volatile struct limine_memmap_request s_memory_map_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0,
};

static volatile struct limine_terminal_request s_terminal_request = {
	.id = LIMINE_TERMINAL_REQUEST,
	.revision = 0,
};

struct limine_hhdm_response *boot_get_hhdm()
{
	return s_hhdm_request.response;
}

struct limine_memmap_response *boot_get_memory_map()
{
	return s_memory_map_request.response;
}

struct limine_terminal_response *boot_get_terminal()
{
	return s_terminal_request.response;
}
