/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/idt.h"

#include "arch/apic.h"
#include "arch/gdt.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/stacktrace.h"

#include <stdint.h>

#define ATTRIBUTE_PRESENT (1 << 7)
#define ATTRIBUTE_INTERRUPT_GATE (1 << 1 | 1 << 2 | 1 << 3)

struct entry
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t attribute;
	uint16_t offset_middle;
	uint32_t offset_high;
	uint32_t zero;
} __attribute__((packed));

struct descriptor
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct entry s_entries[256] = { 0 };
static struct descriptor s_descriptor = { 0 };
static interrupt_handler s_interrupt_handlers[256] = { 0 };

extern void *interrupt_handlers[];

static void idt_register_interrupt_handler(
	struct entry *entry,
	void *handler,
	uint8_t attribute)
{
	assert(entry != NULL);

	const uint64_t handler_address = (uint64_t) handler;

	entry->offset_low = (uint16_t) handler_address;
	entry->selector = KERNEL_CODE_SELECTOR;
	entry->ist = 0;
	entry->attribute = attribute;
	entry->offset_middle = (uint16_t) (handler_address >> 16);
	entry->offset_high = (uint32_t) (handler_address >> 32);
	entry->zero = 0;
}

static void idt_default_interrupt_handler(struct registers *registers)
{
	logger_error("");
	logger_error("An unhandled interrupt 0x%02x occured", registers->isr);
	logger_error("");
	stacktrace_print(50);
	logger_error("");

	for (;;)
	{
		__asm__ __volatile__("cli");
		__asm__ __volatile__("hlt");
	}
}

void idt_raise(struct registers *registers)
{
	s_interrupt_handlers[registers->isr](registers);
	lapic_send_eoi();
}

void idt_init(void)
{
	for (size_t i = 0; i < 256; i++)
	{
		idt_register_interrupt_handler(
			&s_entries[i],
			interrupt_handlers[i],
			ATTRIBUTE_PRESENT | ATTRIBUTE_INTERRUPT_GATE);
		s_interrupt_handlers[i] = idt_default_interrupt_handler;
	}

	s_descriptor.size = sizeof(s_entries) - 1;
	s_descriptor.address = (uintptr_t) s_entries;

	idt_load();

	logger_info("Initialized IDT");
}

void idt_load(void)
{
	__asm__ __volatile__("lidt %0" : : "m"(s_descriptor));
}

void idt_set_handler(size_t interrupt, interrupt_handler handler)
{
	s_interrupt_handlers[interrupt] = handler;
}
