/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Registers.hpp>
#include <Kernel/Common/Optional.hpp>
#include <Kernel/Common/Types.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>

namespace Kernel
{
	class CPU
	{
	public:
		struct Data
		{
			uint16_t cpu_number;
			uintptr_t kernel_stack;
			ssize_t error;
			pid_t pid;
			tid_t tid;
			PageMap* page_map;
		};

	public:
		__attribute__((noreturn)) static void initialize(stivale2_smp_info* smp_info);

		static void write_msr(uint32_t msr, uint64_t value);
		static uint64_t read_msr(uint32_t msr);

		static void write_kernel_gs(uintptr_t address);
		static uintptr_t read_kernel_gs();

		static Optional<CpuId> cpu_id(uint32_t leaf, uint32_t sub_leaf);
	};
} // namespace Kernel
