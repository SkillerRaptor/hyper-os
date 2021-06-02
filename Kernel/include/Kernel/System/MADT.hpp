#pragma once

#include <AK/Vector.hpp>
#include <Kernel/System/ACPI.hpp>
#include <stdint.h>

namespace Kernel
{
	class MADT
	{
	public:
		struct Entry
		{
			ACPI::SDT sdt;
			uint32_t lapic_address;
			uint32_t flags;
			char entries_begin[];
		} __attribute__((packed));
		
		struct Header
		{
			uint8_t type;
			uint8_t length;
		} __attribute__((packed));
		
		struct LAPIC
		{
			Header header;
			uint8_t processor_id;
			uint8_t apic_id;
			uint32_t flags;
		} __attribute__((packed));
		
		struct IOAPIC
		{
			Header header;
			uint8_t apic_id;
			uint8_t reserved;
			uint32_t address;
			uint32_t global_system_interrupt_base;
		} __attribute__((packed));
		
		struct ISO
		{
			Header header;
			uint8_t bus_source;
			uint8_t irq_source;
			uint32_t global_system_interrupt;
			uint16_t flags;
		} __attribute__((packed));
		
		struct NMI
		{
			Header header;
			uint8_t processor;
			uint16_t flags;
			uint8_t lint;
		} __attribute__((packed));
	
	public:
		static void initialize();
	
		static Entry* entry();
		static AK::Vector<LAPIC*> lapics();
		static AK::Vector<IOAPIC*> ioapics();
		static AK::Vector<ISO*> isos();
		static AK::Vector<NMI*> nmis();
		
	private:
		static Entry* s_entry;
		static AK::Vector<LAPIC*> s_lapics;
		static AK::Vector<IOAPIC*> s_ioapics;
		static AK::Vector<ISO*> s_isos;
		static AK::Vector<NMI*> s_nmis;
	};
}
