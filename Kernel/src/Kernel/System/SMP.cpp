/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/MADT.hpp>
#include <Kernel/System/SMP.hpp>
#include <stddef.h>

namespace Kernel
{
	void SMP::initialize(stivale2_struct_tag_smp* smp_tag)
	{
		Logger::info("SMP: Initializing...");

		Logger::debug("SMP: BSP LAPIC id - %x", smp_tag->bsp_lapic_id);
		Logger::debug("SMP: Total CPU count - %u", smp_tag->cpu_count);

		for (size_t i = 0; i < smp_tag->cpu_count; ++i)
		{
			Logger::debug("SMP: Loading processor - %u", MADT::lapics()[i]->processor_id);

			smp_tag->smp_info[i].extra_argument = 0;

			if (smp_tag->smp_info[i].lapic_id == smp_tag->bsp_lapic_id)
			{
				continue;
			}

			auto stack = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(1)) + s_physical_memory_offset;
			smp_tag->smp_info[i].target_stack = stack;
			smp_tag->smp_info[i].goto_address = reinterpret_cast<uint64_t>(CPU::initialize);
		}

		Logger::info("SMP: Initializing finished!");
	}
} // namespace Kernel
