/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/System/MADT.hpp>

namespace Kernel
{
	MADT::Table* MADT::s_table{ nullptr };
	Vector<MADT::LAPIC*> MADT::s_lapics{};
	Vector<MADT::IOAPIC*> MADT::s_ioapics{};
	Vector<MADT::ISO*> MADT::s_isos{};
	Vector<MADT::NMI*> MADT::s_nmis{};

	void MADT::initialize()
	{
		Logger::info("MADT: Initializing...");

		s_table = reinterpret_cast<MADT::Table*>(ACPI::find_sdt("APIC", 0));
		
		auto* entry_begin = reinterpret_cast<uint8_t*>(s_table->entries_begin);
		auto entry_length = reinterpret_cast<uintptr_t>(s_table) + s_table->header.length;
		for (uint8_t* ptr = entry_begin; reinterpret_cast<uintptr_t>(ptr) < entry_length; ptr += *(ptr + 1))
		{
			switch (*(ptr))
			{
			case 0:
				Logger::debug("MADT: Found local APIC #%u", s_lapics.size());
				s_lapics.push_back(reinterpret_cast<MADT::LAPIC*>(ptr));
				break;
			case 1:
				Logger::debug("MADT: Found I/O APIC #%u", s_ioapics.size());
				s_ioapics.push_back(reinterpret_cast<MADT::IOAPIC*>(ptr));
				break;
			case 2:
				Logger::debug("MADT: Found ISO #%u", s_isos.size());
				s_isos.push_back(reinterpret_cast<MADT::ISO*>(ptr));
				break;
			case 4:
				Logger::debug("MADT: Found NMI #%u", s_nmis.size());
				s_nmis.push_back(reinterpret_cast<MADT::NMI*>(ptr));
				break;
			}
		}

		Logger::info("MADT: Initializing finished!");
	}
	
	MADT::Table* MADT::table()
	{
		return s_table;
	}
	
	Vector<MADT::LAPIC*> MADT::lapics()
	{
		return s_lapics;
	}
	
	Vector<MADT::IOAPIC*> MADT::ioapics()
	{
		return s_ioapics;
	}
	
	Vector<MADT::ISO*> MADT::isos()
	{
		return s_isos;
	}
	
	Vector<MADT::NMI*> MADT::nmis()
	{
		return s_nmis;
	}
	
} // namespace Kernel
