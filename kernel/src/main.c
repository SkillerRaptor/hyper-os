/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <limine.h>
#include <stddef.h>

static volatile struct limine_terminal_request s_terminal_request = {
	.id = LIMINE_TERMINAL_REQUEST,
	.revision = 0,
};

__attribute__((noreturn)) void kernel_main(void)
{
	struct limine_terminal_response *response = s_terminal_request.response;
	if (response != NULL && response->terminal_count >= 1)
	{
		response->write(response->terminals[0], "Hello World", 11);
	}

	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}
