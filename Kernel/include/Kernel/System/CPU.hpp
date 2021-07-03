/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Registers.hpp>
#include <Kernel/Common/Optional.hpp>

namespace Kernel
{
	class CPU
	{
	public:
		__attribute__((noreturn)) static void initialize();
		
		static void write_msr(uint32_t msr, uint64_t value);
		static uint64_t read_msr(uint32_t msr);
		
		static Optional<CpuId> cpu_id(uint32_t leaf);
	};
} // namespace Kernel
