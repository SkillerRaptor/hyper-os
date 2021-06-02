#pragma once

namespace Kernel
{
	class APIC
	{
	private:
		static constexpr const uint8_t s_apic_base_msr{ 0x1B };
		
	public:
		static void initialize();
		
		static void lapic_write(uint32_t reg, uint32_t data);
		static uint32_t lapic_read(uint32_t reg);
	};
}
