/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/pic.h"
#include "common/logger.h"

#include <stddef.h>

__attribute__((noreturn)) void kernel_main(void)
{
	logger_init();

	gdt_init();
	pic_remap();
	idt_init();

	logger_info("HyperOS booted successfully");

	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}
