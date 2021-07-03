/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/System/ACPI.hpp>

namespace Kernel
{
	class HPET
	{
	private:
		struct Table
		{
			ACPI::SDT header;
			uint8_t hardware_revision_id;
			uint8_t info;
			uint16_t pci_vendor_id;
			uint8_t address_space_id;
			uint8_t register_bit_width;
			uint8_t register_bit_offset;
			uint8_t reserved;
			uint64_t address;
			uint8_t hpet_number;
			uint16_t minimum_clock_tick;
			uint8_t page_protection;
		} __attribute__((packed));

		struct Entry
		{
			uint64_t general_capabilities;
			uint64_t reserved_1;
			uint64_t general_configuration;
			uint64_t reserved_2;
			uint64_t general_interrupt_status;
			uint64_t reserved_3;
			uint64_t reserved_4[24];
			uint64_t main_counter_value;
			uint64_t reserved_5;
		} __attribute__((packed));
		
	public:
		static void initialize();

	private:
		static Table* s_table;
		static Entry* s_entry;
		
		static size_t s_clock_period;
		static size_t s_frequency;
	};
} // namespace Kernel
