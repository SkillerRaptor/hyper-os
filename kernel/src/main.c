/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/acpi.h"
#include "arch/apic.h"
#include "arch/gdt.h"
#include "arch/hpet.h"
#include "arch/idt.h"
#include "arch/madt.h"
#include "arch/pic.h"
#include "lib/logger.h"
#include "lib/stacktrace.h"
#include "memory/kmalloc.h"
#include "memory/pmm.h"
#include "memory/vmm.h"
#include "scheduling/scheduler.h"
#include "scheduling/smp.h"

__attribute__((noreturn)) static void main_thread(void);

__attribute__((noreturn)) void kernel_main(void)
{
	logger_init();

	gdt_init();
	pic_remap();
	idt_init();

	pmm_init();
	vmm_init();

	stacktrace_init();

	acpi_init();
	madt_init();

	hpet_init();
	apic_init();

	smp_init();
	scheduler_init();

	const int64_t kernel_process_id = scheduler_create_task(NULL);
	scheduler_create_thread(
		kernel_process_id, (uintptr_t) main_thread, KERNEL_CODE_SELECTOR);

	scheduler_wait();
}

__attribute__((noreturn)) static void main_thread(void)
{
	logger_info("HyperOS booted successfully!");

	scheduler_wait();
}
