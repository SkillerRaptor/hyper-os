/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	class PCI
	{
	private:
		static constexpr const uint16_t s_config_address = 0xCF8;
		static constexpr const uint16_t s_config_data = 0xCFC;

	public:
		static void initialize();

		static void write(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset, uint32_t data);
		static uint32_t read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset);

	private:
		static uint16_t get_vendor_id(uint8_t bus, uint8_t device, uint8_t function);
		static uint8_t get_header_type(uint8_t bus, uint8_t device, uint8_t function);

		static void scan_all_buses();
		static void scan_bus(uint8_t bus);
	};
} // namespace Kernel
