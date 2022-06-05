/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/idt.h"

#include "arch/gdt.h"
#include "lib/logger.h"

#include <stddef.h>
#include <stdint.h>

#define ATTRIBUTE_PRESENT (1 << 7)
#define ATTRIBUTE_INTERRUPT_GATE (1 << 1 | 1 << 2 | 1 << 3)

struct Entry
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t attribute;
	uint16_t offset_middle;
	uint32_t offset_high;
	uint32_t zero;
} __attribute__((packed));

struct Descriptor
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct Entry s_entries[256] = { 0 };
static struct Descriptor s_descriptor = { 0 };

extern void *interrupt_handlers[];

static void idt_register_interrupt_handler(
	size_t index,
	void *handler,
	uint8_t attribute)
{
	struct Entry *entry = &s_entries[index];
	uint64_t handler_address = (uint64_t) handler;

	entry->offset_low = (uint16_t) handler_address;
	entry->selector = KERNEL_CODE_SELECTOR;
	entry->ist = 0;
	entry->attribute = attribute;
	entry->offset_middle = (uint16_t) (handler_address >> 16);
	entry->offset_high = (uint32_t) (handler_address >> 32);
	entry->zero = 0;
}

void idt_init(void)
{
	for (size_t i = 0; i < 256; i++)
	{
		idt_register_interrupt_handler(
			i, interrupt_handlers[i], ATTRIBUTE_PRESENT | ATTRIBUTE_INTERRUPT_GATE);
	}

	s_descriptor.size = sizeof(s_entries) - 1;
	s_descriptor.address = (uintptr_t) s_entries;

	idt_load();

	logger_info("Initialized IDT");
}

void idt_load(void)
{
	__asm__ __volatile__("lidt %0" : : "m"(s_descriptor));
	__asm__ __volatile__("sti");
}

void idt_raise(size_t interrupt)
{
	logger_error("Unhandled interrupt 0x%02x", interrupt);
	for (;;)
	{
		__asm__ __volatile__("cli");
		__asm__ __volatile__("hlt");
	}
}
