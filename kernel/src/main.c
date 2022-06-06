/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/acpi.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/madt.h"
#include "arch/pic.h"
#include "lib/logger.h"
#include "memory/pmm.h"
#include "memory/vmm.h"

#include <stddef.h>

__attribute__((noreturn)) void kernel_main(void)
{
	logger_init();

	gdt_init();
	pic_remap();
	idt_init();

	pmm_init();
	vmm_init();

	acpi_init();
	madt_init();

	logger_info("HyperOS booted successfully");

	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}
