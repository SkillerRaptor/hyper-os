/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "arch/acpi.h"

struct madt_header
{
	uint8_t type;
	uint8_t length;
} __attribute__((packed));

struct madt_lapic
{
	struct madt_header header;
	uint8_t processor_id;
	uint8_t id;
	uint32_t flags;
} __attribute__((packed));

struct madt_ioapic
{
	struct madt_header header;
	uint8_t id;
	uint8_t reserved;
	uint32_t address;
	uint32_t gsi_base;
} __attribute__((packed));

struct madt_lapic_list
{
	struct madt_lapic **data;
	size_t size;
};

struct madt_ioapic_list
{
	struct madt_ioapic **data;
	size_t size;
};

void madt_init(void);

struct madt_lapic_list *madt_get_lapics();
struct madt_ioapic_list *madt_get_ioapics();
