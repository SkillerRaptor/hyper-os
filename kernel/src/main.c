/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/acpi.h"
#include "arch/apic.h"
#include "arch/fadt.h"
#include "arch/gdt.h"
#include "arch/hpet.h"
#include "arch/idt.h"
#include "arch/madt.h"
#include "arch/pic.h"
#include "devices/rtc.h"
#include "lib/logger.h"
#include "lib/stacktrace.h"
#include "memory/kmalloc.h"
#include "memory/pmm.h"
#include "memory/vmm.h"
#include "scheduling/scheduler.h"
#include "scheduling/smp.h"

__attribute__((noreturn)) static void kernel_main(void);
__attribute__((noreturn)) static void main_thread(void);

__attribute__((noreturn)) void kernel_early_main(void)
{
	logger_init();
	rtc_init();

	kernel_main();
}

__attribute__((noreturn)) static void kernel_main(void)
{
	gdt_init();
	pic_remap();
	idt_init();

	pmm_init();
	vmm_init();

	stacktrace_init();

	acpi_init();
	madt_init();

	fadt_init();

	hpet_init();
	apic_init();

	smp_init();
	scheduler_init();

	scheduler_create_thread(
		scheduler_get_kernel_process(),
		(uintptr_t) main_thread,
		KERNEL_CODE_SELECTOR);

	scheduler_wait();
}

__attribute__((noreturn)) static void main_thread(void)
{
	const struct date date = rtc_get_date();
	const struct time time = rtc_get_time();
	const time_t current_time = rtc_now();
	logger_info(
		"HyperOS booted successfully on the %02u/%02u/%02u at %02u:%02u:%02u in "
		"%us",
		date.day,
		date.month,
		date.year,
		time.hour,
		time.minute,
		time.second,
		current_time - rtc_get_boot_time());

	scheduler_wait();
}
