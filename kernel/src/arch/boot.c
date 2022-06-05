/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/boot.h"

static volatile struct limine_terminal_request s_terminal_request = {
	.id = LIMINE_TERMINAL_REQUEST,
	.revision = 0,
};

struct limine_terminal_response *boot_get_terminal()
{
	return s_terminal_request.response;
}
