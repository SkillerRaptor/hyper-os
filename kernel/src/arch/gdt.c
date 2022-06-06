/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/gdt.h"

#include "lib/assert.h"
#include "lib/logger.h"

#include <stddef.h>
#include <stdint.h>

#define ACCESS_ATTRIBUTE_NULL (0 << 0)
#define ACCESS_ATTRIBUTE_PRESENT (1 << 7)
#define ACCESS_ATTRIBUTE_CODE_DATA (1 << 4)
#define ACCESS_ATTRIBUTE_EXECUTABLE (1 << 3)
#define ACCESS_ATTRIBUTE_READ_WRITE (1 << 1)

#define FLAG_ATTRIBUTE_NULL (0 << 0)
#define FLAG_ATTRIBUTE_4K (1 << 3)
#define FLAG_ATTRIBUTE_16 (0 << 2)
#define FLAG_ATTRIBUTE_32 (1 << 2)
#define FLAG_ATTRIBUTE_64 (1 << 1)

struct Entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t limit_high : 4;
	uint8_t flags : 4;
	uint8_t base_high;
} __attribute__((packed));

struct Table
{
	struct Entry null_entry;
	struct Entry kernel_entries_16[2];
	struct Entry kernel_entries_32[2];
	struct Entry kernel_entries_64[2];
} __attribute__((packed));

struct Descriptor
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct Table s_table = { 0 };
static struct Descriptor s_descriptor = { 0 };

static void gdt_create_entry(
	struct Entry *entry,
	uint32_t base,
	uint32_t limit,
	uint8_t access,
	uint8_t flags)
{
	assert(entry != NULL);

	entry->limit_low = (uint16_t) (limit & 0x0000ffff);
	entry->base_low = (uint16_t) (base & 0x0000ffff);
	entry->base_middle = (uint8_t) ((base & 0x00ff0000) >> 16);
	entry->access = access;
	entry->limit_high = (uint8_t) ((limit & 0x000f0000) >> 16);
	entry->flags = flags;
	entry->base_high = (uint8_t) ((base & 0xff000000) >> 24);
}

void gdt_init(void)
{
	gdt_create_entry(
		&s_table.null_entry,
		0x00000000,
		0x00000000,
		ACCESS_ATTRIBUTE_NULL,
		FLAG_ATTRIBUTE_NULL);

	gdt_create_entry(
		&s_table.kernel_entries_16[0],
		0x00000000,
		0x0000ffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_EXECUTABLE | ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_16);

	gdt_create_entry(
		&s_table.kernel_entries_16[1],
		0x00000000,
		0x0000ffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_16);

	gdt_create_entry(
		&s_table.kernel_entries_32[0],
		0x00000000,
		0xffffffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_EXECUTABLE | ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_32);

	gdt_create_entry(
		&s_table.kernel_entries_32[1],
		0x00000000,
		0xffffffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_32);

	gdt_create_entry(
		&s_table.kernel_entries_64[0],
		0x00000000,
		0xffffffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_EXECUTABLE | ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_64);

	gdt_create_entry(
		&s_table.kernel_entries_64[1],
		0x00000000,
		0xffffffff,
		ACCESS_ATTRIBUTE_PRESENT | ACCESS_ATTRIBUTE_CODE_DATA |
			ACCESS_ATTRIBUTE_READ_WRITE,
		FLAG_ATTRIBUTE_4K | FLAG_ATTRIBUTE_32);

	s_descriptor.size = sizeof(s_table) - 1;
	s_descriptor.address = (uintptr_t) &s_table;

	gdt_load();

	logger_info("Initialized GDT");
}

void gdt_load(void)
{
	__asm __volatile__("lgdt %0\n"
										 "push %%rbp\n"
										 "mov %%rsp, %%rbx\n"
										 "push %1\n"
										 "push %%rbx\n"
										 "pushf\n"
										 "push %2\n"
										 "push $1f\n"
										 "iretq\n"
										 "1:\n"
										 "pop %%rbp\n"
										 "mov %1, %%ds\n"
										 "mov %1, %%es\n"
										 "mov %1, %%fs\n"
										 "mov %1, %%gs\n"
										 "mov %1, %%ss"
										 :
										 : "m"(s_descriptor),
											 "r"((uint64_t) KERNEL_DATA_SELECTOR),
											 "r"((uint64_t) KERNEL_CODE_SELECTOR)
										 : "memory");
}
