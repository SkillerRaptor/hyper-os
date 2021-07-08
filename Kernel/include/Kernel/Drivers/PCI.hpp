/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Vector.hpp>
#include <stdint.h>

namespace Kernel
{
	class PCI
	{
	public:
		struct Device
		{
			uint8_t bus;
			uint8_t device_code;
			uint8_t function;
			
			uint16_t device_id;
			uint16_t vendor_id;
			uint8_t class_code;
			uint8_t subclass;
			uint8_t prog_if;
		};
		
	private:
		static constexpr const uint16_t s_config_address = 0xCF8;
		static constexpr const uint16_t s_config_data = 0xCFC;

	public:
		static void initialize();

		static void write(uint8_t bus, uint8_t device_code, uint8_t function, uint8_t offset, uint32_t data);
		static uint32_t read(uint8_t bus, uint8_t device_code, uint8_t function, uint8_t offset);

	private:
		static void enumerate_devices();
		
		static void scan_all_buses();
		static void scan_bus(uint8_t bus);
		
		static Device create_device(uint8_t bus, uint8_t device_code, uint8_t function);
		
		static uint16_t get_device_id(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint16_t get_vendor_id(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint8_t get_class_code(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint8_t get_subclass(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint8_t get_prog_if(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint8_t get_header_type(uint8_t bus, uint8_t device_code, uint8_t function);
		static uint8_t get_secondary_bus(uint8_t bus, uint8_t device_code, uint8_t function);
		
	private:
		static Vector<Device> s_devices;
	};
} // namespace Kernel
