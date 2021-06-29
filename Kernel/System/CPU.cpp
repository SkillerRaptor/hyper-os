/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <AK/Logger.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/System/APIC.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/IDT.hpp>
#include <Kernel/System/SMP.hpp>

namespace Kernel
{
	uint64_t CPU::s_current_cpu{ 0 };
	
	void CPU::initialize()
	{
		Kernel::GDT::reload();
		Kernel::IDT::reload();
		
		Kernel::VirtualMemoryManager::switch_page_map(Kernel::VirtualMemoryManager::kernel_page_map());
		
		APIC::lapic_write(APIC::s_apic_base_msr, (APIC::lapic_read(APIC::s_apic_base_msr) | 0x800) & ~(APIC::s_lapic_enable));
		APIC::lapic_enable();
		
		AK::Logger::debug("Current processor id: %u", APIC::lapic_processor_id());
		
		while (true)
		{
			asm volatile("nop");
		}
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
	
	void CPU::write_user_fs(uintptr_t value)
	{
		CPU::write_msr(0xC0000100, value);
	}
	
	uintptr_t CPU::user_fs()
	{
		return CPU::read_msr(0xC0000100);
	}
	
	void CPU::write_user_gs(uintptr_t value)
	{
		CPU::write_msr(0xC0000101, value);
	}
	
	uintptr_t CPU::user_gs()
	{
		return CPU::read_msr(0xC0000101);
	}
	
	void CPU::write_kernel_gs(uintptr_t value)
	{
		CPU::write_msr(0xC0000102, value);
	}
	
	uintptr_t CPU::kernel_gs()
	{
		return CPU::read_msr(0xC0000102);
	}
	
	CPU::LocalData CPU::current_cpu()
	{
		return SMP::cpus()[s_current_cpu];
	}
}
