/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/MADT.hpp>
#include <Kernel/System/SMP.hpp>
#include <stddef.h>

namespace Kernel
{
	Vector<CPU::Data> SMP::s_cpus{};
	uint16_t SMP::s_cpus_online{};
	Spinlock SMP::s_spinlock{};

	void SMP::initialize(stivale2_struct_tag_smp* smp_tag)
	{
		Logger::info("SMP: Initializing...");

		Logger::debug("SMP: BSP LAPIC id - 0x%X", smp_tag->bsp_lapic_id);
		Logger::debug("SMP: Total CPU count - %u", smp_tag->cpu_count);

		s_cpus_online = 1;

		for (size_t i = 0; i < smp_tag->cpu_count; ++i)
		{
			auto stack = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(2)) + Memory::s_physical_memory_offset;

			CPU::Data cpu_data{};
			cpu_data.cpu_number = static_cast<uint16_t>(i);
			cpu_data.kernel_stack = stack;
			cpu_data.error = 0;
			cpu_data.pid = -1;
			cpu_data.tid = -1;
			cpu_data.page_map = VirtualMemoryManager::kernel_page_map();

			s_cpus.push_back(cpu_data);

			if (smp_tag->smp_info[i].lapic_id == smp_tag->bsp_lapic_id)
			{
				CPU::write_kernel_gs(reinterpret_cast<uintptr_t>(&s_cpus[i]));
				continue;
			}

			Logger::info("SMP: Processor %u started...", i);

			smp_tag->smp_info[i].extra_argument = reinterpret_cast<uint64_t>(&s_cpus[i]);
			smp_tag->smp_info[i].target_stack = stack;
			smp_tag->smp_info[i].goto_address = reinterpret_cast<uint64_t>(CPU::initialize);
		}

		while (s_cpus_online < smp_tag->cpu_count)
			;

		Logger::info("SMP: Initializing finished!");
	}

	CPU::Data& SMP::local_cpu()
	{
		int32_t index = 0;

		__asm__ __volatile__(
			"mov %%gs:0, %0"
			: "=r"(index));

		return s_cpus[index];
	}

	Vector<CPU::Data>& SMP::cpus()
	{
		return s_cpus;
	}

	void SMP::cpu_online()
	{
		s_spinlock.lock();
		++s_cpus_online;
		s_spinlock.unlock();
	}
} // namespace Kernel
