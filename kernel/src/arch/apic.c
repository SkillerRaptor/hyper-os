/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/apic.h"

#include "arch/cpu.h"
#include "arch/idt.h"
#include "arch/pic.h"
#include "lib/logger.h"
#include "memory/pmm.h"

#define APIC_BASE_MSR 0x1b

#define LAPIC_EOI_REGISTER 0xb0
#define LAPIC_SPURIOUS_REGISTER 0xf0
#define LAPIC_TIMER_REGISTER 0x320
#define LAPIC_TIMER_INITIAL_COUNT_REGISTER 0x380
#define LAPIC_TIMER_DIVIDER_REGISTER 0x3e0

#define LAPIC_TIMER_ISR 0x20
#define LAPIC_TIMER_PERIODIC 0x20000
#define LAPIC_TIMER_DIVIDER_16 0x3

static void lapic_write(uint32_t lapic_register, uint32_t value)
{
	uint8_t *lapic_address =
		(uint8_t *) (cpu_read_msr(APIC_BASE_MSR) & 0xfffff000);
	*((uint32_t *) (lapic_address + lapic_register)) = value;
}

static uint32_t lapic_read(uint32_t lapic_register)
{
	uint8_t *lapic_address =
		(uint8_t *) (cpu_read_msr(APIC_BASE_MSR) & 0xfffff000);
	return *((uint32_t *) (lapic_address + lapic_register));
}

static void lapic_timer_isr(size_t interrupt)
{
}

static void apic_enable_lapic(uint8_t spurious)
{
	lapic_write(
		LAPIC_SPURIOUS_REGISTER,
		lapic_read(LAPIC_SPURIOUS_REGISTER) | (1 << 8) | 0xff);
}

static void apic_start_timer(void)
{
	// TODO: Calibrate value
	lapic_write(LAPIC_TIMER_REGISTER, LAPIC_TIMER_ISR | LAPIC_TIMER_PERIODIC);
	lapic_write(LAPIC_TIMER_DIVIDER_REGISTER, LAPIC_TIMER_DIVIDER_16);
	lapic_write(LAPIC_TIMER_INITIAL_COUNT_REGISTER, 10000);
}

void apic_init(void)
{
	pic_disable();

	idt_set_handler(LAPIC_TIMER_ISR, lapic_timer_isr);

	apic_enable_lapic(0xff);
	lapic_send_eoi();

	apic_start_timer();

	logger_info("Initialized APIC");

	__asm__ __volatile__("sti");
}

void lapic_send_eoi(void)
{
	lapic_write(LAPIC_EOI_REGISTER, 0);
}
