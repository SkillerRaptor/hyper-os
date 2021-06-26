#include <AK/Logger.hpp>
#include <Kernel/System/MADT.hpp>

namespace Kernel
{
	MADT::Entry* MADT::s_entry{ nullptr };
	AK::Vector<MADT::LAPIC*> MADT::s_lapics{};
	AK::Vector<MADT::IOAPIC*> MADT::s_ioapics{};
	AK::Vector<MADT::ISO*> MADT::s_isos{};
	AK::Vector<MADT::NMI*> MADT::s_nmis{};
	
	void MADT::initialize()
	{
		AK::Logger::info("MADT: Initializing...");
		
		s_entry = reinterpret_cast<MADT::Entry*>(ACPI::find_sdt("APIC", 0));
		
		auto* entry_begin = reinterpret_cast<uint8_t*>(s_entry->entries_begin);
		auto entry_length = reinterpret_cast<uintptr_t>(s_entry) + s_entry->sdt.length;
		for (uint8_t* ptr = entry_begin; reinterpret_cast<uintptr_t>(ptr) < entry_length; ptr += *(ptr + 1))
		{
			switch (*(ptr))
			{
			case 0:
				AK::Logger::debug("MADT: Found local APIC #%u", s_lapics.size());
				s_lapics.push_back(reinterpret_cast<MADT::LAPIC*>(ptr));
				break;
			case 1:
				AK::Logger::debug("MADT: Found I/O APIC #%u", s_ioapics.size());
				s_ioapics.push_back(reinterpret_cast<MADT::IOAPIC*>(ptr));
				break;
			case 2:
				AK::Logger::debug("MADT: Found ISO #%u", s_isos.size());
				s_isos.push_back(reinterpret_cast<MADT::ISO*>(ptr));
				break;
			case 4:
				AK::Logger::debug("MADT: Found NMI #%u", s_nmis.size());
				s_nmis.push_back(reinterpret_cast<MADT::NMI*>(ptr));
				break;
			}
		}
		
		AK::Logger::info("MADT: Initializing finished!");
	}
	
	MADT::Entry* MADT::entry()
	{
		return s_entry;
	}
	
	AK::Vector<MADT::LAPIC*> MADT::lapics()
	{
		return s_lapics;
	}
	
	AK::Vector<MADT::IOAPIC*> MADT::ioapics()
	{
		return s_ioapics;
	}
	
	AK::Vector<MADT::ISO*> MADT::isos()
	{
		return s_isos;
	}
	
	AK::Vector<MADT::NMI*> MADT::nmis()
	{
		return s_nmis;
	}
}
