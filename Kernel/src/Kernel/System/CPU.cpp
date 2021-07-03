/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/IDT.hpp>
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
} // namespace Kernel
