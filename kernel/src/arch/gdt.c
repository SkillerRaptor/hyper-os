/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/gdt.h"

#include "lib/assert.h"
#include "lib/logger.h"
#include "scheduling/spinlock.h"

#include <stddef.h>

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

#define TSS_TYPE_PRESENT (1 << 3)
#define TSS_TYPE_INACTIVE (1 << 3 | 1 << 0)

#define TSS_SELECTOR 0x38

static struct spinlock s_lock;

struct entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t limit_high : 4;
	uint8_t flags : 4;
	uint8_t base_high;
} __attribute__((packed));

struct tss_entry
{
	uint16_t length;
	uint16_t base_low;
	uint8_t base_middle_1;
	uint8_t flags_low;
	uint8_t flags_high;
	uint8_t base_middle_2;
	uint32_t base_high;
	uint32_t reserved;
} __attribute__((packed));

struct table
{
	struct entry null_entry;
	struct entry kernel_entries_16[2];
	struct entry kernel_entries_32[2];
	struct entry kernel_entries_64[2];
	struct tss_entry tss_entry;
} __attribute__((packed));

struct descriptor
{
	uint16_t size;
	uint64_t address;
} __attribute__((packed));

static struct table s_table = { 0 };
static struct descriptor s_descriptor = { 0 };

static void gdt_create_entry(
	struct entry *entry,
	uint32_t base,
	uint32_t limit,
	uint8_t access,
	uint8_t flags);

static void gdt_create_tss_entry(
	struct tss_entry *tss_entry,
	uintptr_t address);

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

	logger_info("GDT: Created kernel entries");

	gdt_create_tss_entry(&s_table.tss_entry, 0);

	logger_info("GDT: Created TSS entry");

	s_descriptor.size = sizeof(s_table) - 1;
	s_descriptor.address = (uintptr_t) &s_table;

	gdt_load();

	logger_info("GDT: Initialized");
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
										 : "rbx", "memory");
}

void gdt_load_tss(struct tss *tss)
{
	spinlock_lock(&s_lock);

	assert(tss != NULL);

	gdt_create_tss_entry(&s_table.tss_entry, (uintptr_t) tss);

	__asm__ __volatile__("ltr %0" : : "rm"((uint16_t) TSS_SELECTOR) : "memory");

	spinlock_unlock(&s_lock);
}

static void gdt_create_entry(
	struct entry *entry,
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

static void gdt_create_tss_entry(struct tss_entry *tss_entry, uintptr_t address)
{
	assert(tss_entry != NULL);

	tss_entry->length = sizeof(struct tss);
	tss_entry->base_low = (uint16_t) (address & 0xffff);
	tss_entry->base_middle_1 = (uint8_t) ((address >> 16) & 0xff);
	tss_entry->flags_low = (TSS_TYPE_PRESENT << 4) | TSS_TYPE_INACTIVE;
	tss_entry->flags_high = 0;
	tss_entry->base_middle_2 = (uint8_t) ((address >> 24) & 0xff);
	tss_entry->base_high = (uint32_t) (address >> 32);
	tss_entry->reserved = 0;
}
