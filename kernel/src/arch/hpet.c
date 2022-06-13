/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/hpet.h"

#include "arch/acpi.h"
#include "lib/assert.h"
#include "lib/logger.h"

struct hpet_general_capabilities
{
	uint8_t revision_id;
	uint8_t timer_amount : 5;
	uint8_t count_size : 1;
	uint8_t reserved : 1;
	uint8_t legacy_replacement : 1;
	uint16_t vendor_id;
	uint32_t counter_clock_period;
} __attribute__((packed));

struct hpet_general_configuration
{
	uint8_t enable : 1;
	uint8_t legacy_replacement : 1;
	uint64_t reserved : 62;
} __attribute__((packed));

struct hpet_entry
{
	struct hpet_general_capabilities general_capabilities;
	uint64_t reserved_1;
	struct hpet_general_configuration general_configuration;
	uint64_t reserved_2;
	uint64_t general_interrupt_status;
	uint64_t reserved_3;
	uint64_t reserved_4[24];
	uint64_t main_counter_value;
	uint64_t reserved_5;
} __attribute__((packed));

struct hpet_address_entry
{
	uint8_t address_space_id;
	uint8_t register_bit_width;
	uint8_t register_bit_offset;
	uint8_t reserved;
	uint64_t address;
} __attribute__((packed));

struct hpet_table
{
	struct sdt header;
	uint8_t hardware_revision_id;
	uint8_t comparator_count : 5;
	uint8_t counter_size : 1;
	uint8_t reserved : 1;
	uint8_t legacy_replacement : 1;
	uint16_t pci_vendor_id;
	struct hpet_address_entry address;
	uint8_t hpet_number;
	uint16_t minimum_tick;
	uint8_t page_protection;
} __attribute__((packed));

static struct hpet_table *s_table = NULL;
static struct hpet_entry *s_entry = NULL;

static uint64_t s_clock = 0;

void hpet_init(void)
{
	s_table = (struct hpet_table *) acpi_find_sdt("HPET", 0);
	assert(s_table != NULL);

	s_entry = (struct hpet_entry *) s_table->address.address;
	assert(s_entry != NULL);

	s_clock = s_entry->general_capabilities.counter_clock_period;
	logger_info("HPET: Configured clock period with %uns", s_clock / 1000000);

	s_entry->general_configuration.enable = 0;
	s_entry->main_counter_value = 0;
	s_entry->general_configuration.enable = 1;

	logger_info("HPET: Initialized");
}

void hpet_sleep(uint64_t milliseconds)
{
	const uint64_t ticks =
		s_entry->main_counter_value + (milliseconds * 1000000000000) / s_clock;
	while (s_entry->main_counter_value < ticks)
	{
	}
}
