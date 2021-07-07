/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Common/MMIO.hpp>
#include <Kernel/Drivers/HPET.hpp>
#include <Kernel/System/ACPI.hpp>

namespace Kernel
{
	HPET::Table* HPET::s_table{ nullptr };
	HPET::Entry* HPET::s_entry{ nullptr };

	size_t HPET::s_clock_period{ 0 };

	void HPET::initialize()
	{
		Logger::info("HPET: Initializing...");

		s_table = reinterpret_cast<HPET::Table*>(ACPI::find_sdt("HPET", 0));
		s_entry = reinterpret_cast<HPET::Entry*>(s_table->address + s_physical_memory_offset);

		s_clock_period = static_cast<size_t>(s_entry->general_capabilities >> 32);

		s_entry->general_configuration = 1;

		Logger::info("HPET: Initializing finished!");
	}

	void HPET::sleep(uint64_t ms)
	{
		uint64_t ticks = s_entry->main_counter_value + (ms * 1000000000000) / s_clock_period;
		
		Logger::debug("Ticks: %u, Counter Value: %u", ticks, s_entry->main_counter_value);
		
		__volatile__ uint64_t i_ = 0;
		while (s_entry->main_counter_value < ticks)
		{
			__asm__ __volatile__(
				""
				: "+g" (i_)
				:
				:
			);
		}
	}
} // namespace Kernel
