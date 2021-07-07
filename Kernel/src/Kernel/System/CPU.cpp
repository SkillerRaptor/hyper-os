/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Interrupts/APIC.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/SMP.hpp>

namespace Kernel
{
	void CPU::initialize(stivale2_smp_info* smp_info)
	{
		GDT::install();
		IDT::install();
		
		VirtualMemoryManager::switch_page_map(VirtualMemoryManager::kernel_page_map());
		
		write_kernel_gs(reinterpret_cast<uintptr_t>(smp_info->extra_argument));
		
		APIC::calibrate(100);
		uint32_t spur = APIC::lapic_read(0xF0);
		APIC::lapic_write(0xF0, spur | (1 << 8) | 0xFF);

		Logger::info("Processor %u started successfully!", SMP::local_cpu().cpu_number);
		SMP::cpu_online();
		
		__asm__ __volatile__("sti");

		while (true)
		{
			__asm__ __volatile__("hlt");
		}
	}
	
	void CPU::write_msr(uint32_t msr, uint64_t value)
	{
		uint32_t edx = value >> 32;
		uint32_t eax = static_cast<uint32_t>(value);
		
		__asm__ __volatile__(
			"wrmsr"
			:
			: "a" (eax)
			, "d" (edx)
			, "c" (msr)
			: "memory"
		);
	}
	
	uint64_t CPU::read_msr(uint32_t msr)
	{
		uint32_t edx = 0;
		uint32_t eax = 0;
		
		__asm__ __volatile__(
			"rdmsr"
			: "=a" (eax)
			, "=d" (edx)
			: "c" (msr)
			: "memory"
		);
		
		return ((static_cast<uint64_t>(edx) << 32) | eax);
	}
	
	void CPU::write_kernel_gs(uintptr_t address)
	{
		write_msr(0xC0000101, address);
	}
	
	uintptr_t CPU::read_kernel_gs()
	{
		return read_msr(0xC0000101);
	}
	
	Optional<CpuId> CPU::cpu_id(uint32_t leaf, uint32_t sub_leaf)
	{
		uint32_t cpuid_max = 0;
		__asm__ __volatile__ (
			"cpuid"
			: "=a" (cpuid_max)
			: "a" (leaf & 0x80000000)
			: "rbx"
			, "rcx"
			, "rdx"
		);
		
		if (leaf > cpuid_max)
		{
			return {};
		}
		
		CpuId cpu_id{};
		cpu_id.leaf = leaf;
		cpu_id.sub_leaf = sub_leaf;
		
		__asm__ __volatile__ (
			"cpuid"
			: "=a" (cpu_id.eax)
			, "=b" (cpu_id.ebx)
			, "=c" (cpu_id.ecx)
			, "=d" (cpu_id.edx)
			: "a" (leaf)
			, "c" (0)
		);
		
		return cpu_id;
	}
} // namespace Kernel
