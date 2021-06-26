#include <AK/Logger.hpp>
#include <AK/Memory.hpp>
#include <Kernel/System/APIC.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/MADT.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	void* APIC::s_apic_address{ nullptr };
	
	void APIC::initialize()
	{
		AK::Logger::info("APIC: Initializing...");
		
		s_apic_address = reinterpret_cast<void*>(MADT::entry()->lapic_address);
		
		APIC::lapic_write(s_apic_base_msr, (APIC::lapic_read(s_apic_base_msr) | 0x800) & ~(s_lapic_enable));
		APIC::lapic_enable();
		
		PIC::disable();
		
		AK::Logger::info("APIC: Initializing finished!");
	}
	
	void APIC::lapic_write(uint32_t reg, uint32_t data)
	{
		*reinterpret_cast<volatile uint32_t*>(APIC::lapic_mmio_base() + reg) = data;
	}
	
	uint32_t APIC::lapic_read(uint32_t reg)
	{
		return *reinterpret_cast<volatile uint32_t*>(APIC::lapic_mmio_base() + reg);
	}
	
	void APIC::lapic_enable()
	{
		APIC::lapic_write(s_lapic_register_spurious, APIC::lapic_read(s_lapic_register_spurious) | 0x01FF);
	}
	
	void APIC::lapic_end_of_interrupt()
	{
		APIC::lapic_write(s_lapic_register_end_of_interrupt, 0);
	}
	
	uintptr_t APIC::lapic_mmio_base()
	{
		return reinterpret_cast<uintptr_t>((CPU::read_msr(s_apic_base_msr) & 0xFFFFF000) + AK::s_physical_memory_offset);
	}
	
	uint32_t APIC::lapic_processor_id()
	{
		return APIC::lapic_read(CPU::current_cpu().lapic_id) >> 24;
	}
}
