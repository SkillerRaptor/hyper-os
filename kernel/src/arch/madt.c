/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/madt.h"

#include "arch/acpi.h"
#include "lib/logger.h"

struct madt_table
{
	struct sdt header;
	uint32_t lapic_address;
	uint32_t flags;
	uint8_t entries[];
} __attribute__((packed));

static struct madt_table *s_table = NULL;
static VECTOR_TYPE(struct madt_lapic *) s_lapics = NULL;
static VECTOR_TYPE(struct madt_ioapic *) s_ioapics = NULL;

void madt_init(void)
{
	s_table = (struct madt_table *) acpi_find_sdt("APIC", 0);

	const uintptr_t length = (uintptr_t) s_table + s_table->header.length;
	for (uint8_t *ptr = s_table->entries; (uintptr_t) ptr < length;
			 ptr += *(ptr + 1))
	{
		const uint8_t type = *ptr;
		switch (type)
		{
		case 0:
		{
			struct madt_lapic *lapic = (struct madt_lapic *) ptr;
			VECTOR_PUSH_BACK(s_lapics, lapic);
			break;
		}
		case 1:
		{
			struct madt_ioapic *ioapic = (struct madt_ioapic *) ptr;
			VECTOR_PUSH_BACK(s_ioapics, ioapic);
			break;
		}
		default:
			break;
		}
	}

	logger_info("Initialized MADT");
}

VECTOR_TYPE(struct madt_lapic *) madt_get_lapics()
{
	return s_lapics;
}

VECTOR_TYPE(struct madt_ioapic *) madt_get_ioapics()
{
	return s_ioapics;
}
