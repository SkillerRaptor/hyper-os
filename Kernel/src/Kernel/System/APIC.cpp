#include <AK/Logger.hpp>
#include <AK/Memory.hpp>
#include <Kernel/System/APIC.hpp>
#include <Kernel/System/CPU.hpp>

namespace Kernel
{
	void APIC::initialize()
	{
		AK::Logger::info("APIC: Initializing...");
		
		AK::Logger::info("APIC: Initializing finished!");
	}
	
	void APIC::lapic_write(uint32_t reg, uint32_t data)
	{
		auto lapic_mmio_base = reinterpret_cast<uintptr_t>((CPU::read_msr(s_apic_base_msr) & 0xFFFFF000) + AK::s_physical_memory_offset);
		*reinterpret_cast<volatile uint32_t*>(lapic_mmio_base + reg) = data;
	}
	
	uint32_t APIC::lapic_read(uint32_t reg)
	{
		auto lapic_mmio_base = reinterpret_cast<uintptr_t>((CPU::read_msr(s_apic_base_msr) & 0xFFFFF000) + AK::s_physical_memory_offset);
		return *reinterpret_cast<volatile uint32_t*>(lapic_mmio_base + reg);
	}
	
	void APIC::lapic_enable(uint8_t spurious_vector)
	{
		APIC::lapic_write(s_lapic_register_spurious, APIC::lapic_read(s_lapic_register_spurious) | (1 << 8) | spurious_vector);
	}
	
	void APIC::lapic_end_of_interrupt()
	{
		APIC::lapic_write(s_lapic_register_end_of_interrupt, 0);
	}
}
