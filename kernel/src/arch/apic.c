/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/apic.h"

#include "arch/cpu.h"
#include "arch/hpet.h"
#include "arch/pic.h"
#include "lib/logger.h"
#include "memory/pmm.h"

#define APIC_BASE_MSR 0x1b

#define LAPIC_ENABLE 0x800

#define LAPIC_SPURIOUS_ALL 0xff
#define LAPIC_SPURIOUS_ENABLE_APIC 0x100

#define LAPIC_ID_REGISTER 0x20
#define LAPIC_EOI_REGISTER 0xb0
#define LAPIC_SPURIOUS_REGISTER 0xf0
#define LAPIC_TIMER_REGISTER 0x320
#define LAPIC_TIMER_INITIAL_COUNT_REGISTER 0x380
#define LAPIC_TIMER_CURRENT_COUNT_REGISTER 0x390
#define LAPIC_TIMER_DIVIDER_REGISTER 0x3e0

#define LAPIC_TIMER_MASKED 0x10000
#define LAPIC_TIMER_PERIODIC 0x20000
#define LAPIC_TIMER_DIVIDER_16 0x3

static void lapic_init(void);
static void lapic_timer_init(void);

void apic_init(void)
{
	pic_disable();

	lapic_init();
	lapic_timer_init();

	logger_info("APIC: Initialized");
}

/*
 * LAPIC
 */

static void lapic_write(uint32_t lapic_register, uint32_t value);
static uint32_t lapic_read(uint32_t lapic_register);

void lapic_enable(void)
{
	lapic_write(
		LAPIC_SPURIOUS_REGISTER,
		lapic_read(LAPIC_SPURIOUS_REGISTER) | LAPIC_SPURIOUS_ENABLE_APIC |
			LAPIC_SPURIOUS_ALL);
}

void lapic_send_eoi(void)
{
	lapic_write(LAPIC_EOI_REGISTER, 0);
}

uint8_t lapic_get_current_cpu()
{
	return (uint8_t) (lapic_read(LAPIC_ID_REGISTER) >> 24);
}

void lapic_init(void)
{
	cpu_write_msr(
		APIC_BASE_MSR, (cpu_read_msr(APIC_BASE_MSR) | LAPIC_ENABLE) & ~((1 << 10)));

	lapic_enable();

	logger_info("APIC: LAPIC initialized");
}

static void lapic_timer_init(void)
{
	lapic_write(LAPIC_TIMER_DIVIDER_REGISTER, LAPIC_TIMER_DIVIDER_16);
	lapic_write(LAPIC_TIMER_INITIAL_COUNT_REGISTER, 0xFFFFFFFF);

	hpet_sleep(10);

	lapic_write(LAPIC_TIMER_REGISTER, LAPIC_TIMER_MASKED);

	const uint32_t ticks =
		(0xffffffff - lapic_read(LAPIC_TIMER_CURRENT_COUNT_REGISTER)) / 10;
	logger_info("APIC: LAPIC timer configured with %u ticks", ticks);

	lapic_write(LAPIC_TIMER_REGISTER, LAPIC_TIMER_ISR | LAPIC_TIMER_PERIODIC);
	lapic_write(LAPIC_TIMER_DIVIDER_REGISTER, LAPIC_TIMER_DIVIDER_16);
	lapic_write(LAPIC_TIMER_INITIAL_COUNT_REGISTER, ticks);

	logger_info("APIC: LAPIC timer initialized");
}

static void lapic_write(uint32_t lapic_register, uint32_t value)
{
	uint8_t *lapic_address =
		(uint8_t *) (cpu_read_msr(APIC_BASE_MSR) & 0xfffff000);
	*((volatile uint32_t *) (lapic_address + lapic_register)) = value;
}

static uint32_t lapic_read(uint32_t lapic_register)
{
	uint8_t *lapic_address =
		(uint8_t *) (cpu_read_msr(APIC_BASE_MSR) & 0xfffff000);
	return *((volatile uint32_t *) (lapic_address + lapic_register));
}
