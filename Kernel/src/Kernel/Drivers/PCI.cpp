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
	void PCI::initialize()
	{
		Logger::info("PCI: Initializing...");

		PCI::scan_all_buses();

		Logger::info("PCI: Initializing finished!");
	}

	void PCI::write(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset, uint32_t data)
	{
		uint32_t value = 0;
		value |= 1 << 31;
		value |= static_cast<uint32_t>(bus) << 16;
		value |= static_cast<uint32_t>(device) & 31 << 11;
		value |= static_cast<uint32_t>(function) & 7 << 8;
		value |= static_cast<uint32_t>(offset) & ~3;

		IoService::outd(s_config_address, value);
		IoService::outd(s_config_data, data);
	}

	uint32_t PCI::read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
	{
		uint32_t value = 0;
		value |= 1 << 31;
		value |= static_cast<uint32_t>(bus) << 16;
		value |= static_cast<uint32_t>(device) & 31 << 11;
		value |= static_cast<uint32_t>(function) & 7 << 8;
		value |= static_cast<uint32_t>(offset) & ~3;

		IoService::outd(s_config_address, value);
		return IoService::ind(s_config_data);
	}

	uint16_t PCI::get_vendor_id(uint8_t bus, uint8_t device, uint8_t function)
	{
		return static_cast<uint16_t>(PCI::read(bus, device, function, 0x00));
	}

	uint8_t PCI::get_header_type(uint8_t bus, uint8_t device, uint8_t function)
	{
		return static_cast<uint8_t>(PCI::read(bus, device, function, 0x0C) >> 16);
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
		for (uint8_t device = 0; device < 32; ++device)
		{
			if (PCI::get_vendor_id(bus, device, 0) == 0xFFFF)
			{
				continue;
			}

			Logger::debug("PCI: Device found! Bus: (0x%02X), Device: (0x%02X), Function: (0x%02X)", bus, device, 0);

			if (PCI::get_header_type(bus, device, 0) & (1 << 7))
			{
			}
		}
	}
} // namespace Kernel
