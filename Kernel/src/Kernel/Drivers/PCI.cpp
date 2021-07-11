/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/IoService.hpp>
#include <Kernel/Common/Logger.hpp>
#include <Kernel/Drivers/PCI.hpp>

namespace Kernel
{
	Vector<PCI::Device> PCI::s_devices;

	void PCI::initialize()
	{
		Logger::info("PCI: Initializing...");

		PCI::scan_all_buses();
		PCI::enumerate_devices();

		Logger::info("PCI: Initializing finished!");
	}

	void PCI::enumerate_devices()
	{
		for (size_t i = 0; i < s_devices.size(); ++i)
		{
			const Device& device = s_devices[i];

			Logger::debug("PCI: Device %02u", i);
			Logger::debug(
				"PCI: Vendor: (0x%04X), Bus: (0x%02X), Function: (0x%02X)",
				device.vendor_id,
				device.bus,
				device.function);
			Logger::debug(
				"PCI: Class: (0x%02X), Subclass: (0x%02X), Prog IF: (0x%02X), Device Id: (0x%02X)",
				device.class_code,
				device.subclass,
				device.prog_if,
				device.device_id);

			switch (device.class_code)
			{
			case 0x01:
				switch (device.subclass)
				{
				case 0x06:
					// TODO: AHCI
					break;
				case 0x08:
					// TODO: NVMe
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	void PCI::scan_all_buses()
	{
		for (uint16_t bus = 0; bus < 256; ++bus)
		{
			PCI::scan_bus(static_cast<uint8_t>(bus));
		}
	}

	void PCI::scan_bus(uint8_t bus)
	{
		for (uint8_t device_code = 0; device_code < 32; ++device_code)
		{
			if (PCI::get_vendor_id(bus, device_code, 0) == 0xFFFF)
			{
				continue;
			}

			s_devices.push_back(PCI::create_device(bus, device_code, 0));

			if (!(PCI::get_header_type(bus, device_code, 0) & (1 << 7)))
			{
				continue;
			}

			for (uint8_t function = 1; function < 8; ++function)
			{
				if (PCI::get_vendor_id(bus, device_code, function) == 0xFFFF)
				{
					continue;
				}

				s_devices.push_back(PCI::create_device(bus, device_code, function));
			}
		}
	}

	PCI::Device PCI::create_device(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		PCI::Device device{};
		device.bus = bus;
		device.device_code = device_code;
		device.function = function;
		device.device_id = PCI::get_device_id(bus, device_code, function);
		device.vendor_id = PCI::get_vendor_id(bus, device_code, function);
		device.class_code = PCI::get_class_code(bus, device_code, function);
		device.subclass = PCI::get_subclass(bus, device_code, function);
		device.prog_if = PCI::get_prog_if(bus, device_code, function);

		if (PCI::get_header_type(bus, device_code, function) & ~(1 << 7))
		{
			PCI::scan_bus(PCI::get_secondary_bus(bus, device_code, function));
		}

		return device;
	}
	
	Optional<PCI::Bar> PCI::get_bar(const Device& device, size_t index)
	{
		if (PCI::get_header_type(device.bus, device.device_code, device.function) != 0x00)
		{
			return {};
		}
		
		if (index > 5)
		{
			return {};
		}
		
		uint8_t bar_table_offset = 0x10 + index * 0x04;
		
		uint32_t bar_low = PCI::read(device, bar_table_offset);
		PCI::write(device, bar_table_offset, ~0);
		
		size_t bar_size_low = PCI::read(device, bar_table_offset);
		PCI::write(device, bar_table_offset, bar_low);
		
		bool is_mmio = !(bar_low & 1);
		if (((bar_low >> 1) & 0b11) == 0b10)
		{
			uint32_t bar_high = PCI::read(device, bar_table_offset + 4);
			PCI::write(device, bar_table_offset + 4, ~0);
			
			uint32_t bar_size_high = PCI::read(device, bar_table_offset + 4);
			PCI::write(device, bar_table_offset + 4, bar_high);
			
			size_t size = ((static_cast<uint64_t>(bar_size_high) << 32) | bar_size_low) & ~(is_mmio ? 0b1111 : 0b11);
			size = ~size + 1;
			
			size_t base = ((static_cast<uint64_t>(bar_high) << 32) | bar_low) & ~(is_mmio ? 0b1111 : 0b11);
			return Bar{ base, size };
		}
		
		size_t size = bar_size_low & (is_mmio ? 0b1111 : 0b11);
		size = ~size + 1;
		
		return Bar{ bar_low, size };
	}
	
	void PCI::become_bus_master(const PCI::Device& device)
	{
		PCI::write(device, 0x04, PCI::read(device, 0x04) | (1 << 2));
	}
	
	void PCI::enable_mmio(const PCI::Device& device)
	{
		PCI::write(device, 0x04, PCI::read(device, 0x04) | (1 << 1));
	}

	uint16_t PCI::get_device_id(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint16_t>(PCI::read(bus, device_code, function, 0x0) >> 16);
	}

	uint16_t PCI::get_vendor_id(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint16_t>(PCI::read(bus, device_code, function, 0x00) >> 0);
	}

	uint8_t PCI::get_class_code(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device_code, function, 0x08) >> 24);
	}

	uint8_t PCI::get_subclass(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device_code, function, 0x08) >> 16);
	}

	uint8_t PCI::get_prog_if(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device_code, function, 0x08) >> 8);
	}

	uint8_t PCI::get_header_type(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device_code, function, 0x0C) >> 16);
	}

	uint8_t PCI::get_secondary_bus(uint8_t bus, uint8_t device_code, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device_code, function, 0x18) >> 8);
	}
	
	void PCI::write(const PCI::Device& device, uint8_t offset, uint32_t data)
	{
		PCI::write(device.bus, device.device_code, device.function, offset, data);
	}

	void PCI::write(uint8_t bus, uint8_t device_code, uint8_t function, uint8_t offset, uint32_t data)
	{
		uint32_t value = 0;
		value |= 1 << 31;
		value |= static_cast<uint32_t>(bus) << 16;
		value |= (static_cast<uint32_t>(device_code) & 31) << 11;
		value |= (static_cast<uint32_t>(function) & 7) << 8;
		value |= static_cast<uint32_t>(offset) & ~3;

		IoService::outd(s_config_address, value);
		IoService::outd(s_config_data, data);
	}
	
	uint32_t PCI::read(const PCI::Device& device, uint8_t offset)
	{
		return PCI::read(device.bus, device.device_code, device.function, offset);
	}

	uint32_t PCI::read(uint8_t bus, uint8_t device_code, uint8_t function, uint8_t offset)
	{
		uint32_t value = 0;
		value |= 1 << 31;
		value |= static_cast<uint32_t>(bus) << 16;
		value |= (static_cast<uint32_t>(device_code) & 31) << 11;
		value |= (static_cast<uint32_t>(function) & 7) << 8;
		value |= static_cast<uint32_t>(offset) & ~3;

		IoService::outd(s_config_address, value);
		return IoService::ind(s_config_data);
	}
} // namespace Kernel
