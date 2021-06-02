#include <AK/Logger.hpp>
#include <Kernel/System/APIC.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	void CPU::initialize(stivale2_smp_info* smp_info)
	{
		AK::Logger::info("CPU: Initializing...");
		
		PIC::disable();
		APIC::lapic_enable(0xFF);
		
		AK::Logger::info("CPU: Initializing finished!");
	}
	
	uint64_t CPU::read_timestamp()
	{
		uint32_t low = 0;
		uint32_t high = 0;
		
		asm volatile(
		"rdtsc"
		: "=a"(low), "=d"(high)
		);
		
		return (static_cast<uint64_t>(high) << 32) | low;
	}
	
	void CPU::invalidate_page(void* m)
	{
		asm volatile(
		"invlpg (%0)"
		:
		: "b"(m)
		: "memory"
		);
	}
	
	void CPU::write_msr(uint64_t msr, uint64_t value)
	{
		uint32_t low = value & 0xFFFFFFFF;
		uint32_t high = value >> 32;
		
		asm volatile(
		"wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high)
		);
	}
	
	uint64_t CPU::read_msr(uint64_t msr)
	{
		uint32_t low = 0;
		uint32_t high = 0;
		
		asm volatile(
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr)
		);
		
		return (static_cast<uint64_t>(high) << 32) | low;
	}
}
