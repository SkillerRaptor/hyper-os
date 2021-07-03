/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/CPU.hpp>

namespace Kernel
{
	void CPU::initialize()
	{
		GDT::install();
		IDT::install();

		Logger::info("Processor %u successfully loaded!");

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
	
	Optional<CpuId> CPU::cpu_id(uint32_t leaf)
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
			return {};
		
		CpuId cpu_id{};
		
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
