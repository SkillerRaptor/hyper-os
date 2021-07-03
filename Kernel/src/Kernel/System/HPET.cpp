/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Common/MMIO.hpp>
#include <Kernel/System/ACPI.hpp>
#include <Kernel/System/HPET.hpp>

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

		MMIO::outq(&s_entry->general_configuration, 1);

		Logger::info("HPET: Initializing finished!");
	}

	void HPET::sleep(uint64_t ms)
	{
		uint64_t ticks = MMIO::inq(&s_entry->main_counter_value) + (ms * 1000000000000) / s_clock_period;
		while(MMIO::inq(&s_entry->main_counter_value) < ticks);
	}
} // namespace Kernel
