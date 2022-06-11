/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/madt.h"

#include "arch/acpi.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "memory/kmalloc.h"

struct madt_table
{
	struct sdt header;
	uint32_t lapic_address;
	uint32_t flags;
	uint8_t entries[];
} __attribute__((packed));

static struct madt_table *s_table = NULL;
static struct madt_lapic_list s_lapics = { 0 };
static struct madt_ioapic_list s_ioapics = { 0 };

void madt_init(void)
{
	s_table = (struct madt_table *) acpi_find_sdt("APIC", 0);
	assert(s_table != NULL);

	uint8_t *begin = s_table->entries;
	const uintptr_t length = (uintptr_t) s_table + s_table->header.length;
	for (uint8_t *ptr = begin; (uintptr_t) ptr < length; ptr += *(ptr + 1))
	{
		const uint8_t type = *ptr;
		switch (type)
		{
		case 0:
			++s_lapics.size;
			break;
		case 1:
			++s_ioapics.size;
			break;
		default:
			break;
		}
	}

	s_lapics.data = kmalloc(s_lapics.size * sizeof(struct madt_lapic));
	s_ioapics.data = kmalloc(s_ioapics.size * sizeof(struct madt_ioapic));

	size_t current_lapic_index = 0;
	size_t current_ioapic_index = 0;
	for (uint8_t *ptr = begin; (uintptr_t) ptr < length; ptr += *(ptr + 1))
	{
		const uint8_t type = *ptr;
		switch (type)
		{
		case 0:
		{
			struct madt_lapic *lapic = (struct madt_lapic *) ptr;
			s_lapics.data[current_lapic_index] = lapic;
			++current_lapic_index;
			break;
		}
		case 1:
		{
			struct madt_ioapic *ioapic = (struct madt_ioapic *) ptr;
			s_ioapics.data[current_ioapic_index] = ioapic;
			++current_ioapic_index;
			break;
		}
		default:
			break;
		}
	}

	logger_info("Initialized MADT");
}

struct madt_lapic_list *madt_get_lapics()
{
	return &s_lapics;
}

struct madt_ioapic_list *madt_get_ioapics()
{
	return &s_ioapics;
}
