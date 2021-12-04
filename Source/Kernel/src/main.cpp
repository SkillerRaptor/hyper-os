/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <stivale2.h>
#pragma GCC diagnostic pop

extern "C"
{
	[[noreturn]] void KernelMain(struct stivale2_struct *bootloader_info)
	{
		(void) bootloader_info;
		while (true)
		{
			asm volatile("sti");
			asm volatile("hlt");
		}
	}
}
