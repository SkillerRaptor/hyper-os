#pragma once

namespace Kernel
{
	class APIC
	{
	private:
		static constexpr const uint8_t s_apic_base_msr{ 0x1B };
		static constexpr const uint16_t s_lapic_register_end_of_interrupt{ 0x00B0 };
		static constexpr const uint16_t s_lapic_register_spurious{ 0x00F0 };
		
	public:
		static void initialize();
		
		static void lapic_write(uint32_t reg, uint32_t data);
		static uint32_t lapic_read(uint32_t reg);
		
		static void lapic_enable(uint8_t spurious_vector);
		static void lapic_end_of_interrupt();
		
	private:
		static uintptr_t lapic_mmio_base();
	};
}
