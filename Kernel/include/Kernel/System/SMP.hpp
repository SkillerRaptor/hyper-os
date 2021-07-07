/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Vector.hpp>
#include <Kernel/System/CPU.hpp>
#include <stivale2.h>

namespace Kernel
{
	class SMP
	{
	public:
		static void initialize(stivale2_struct_tag_smp* smp_tag);
	
		static CPU::Data& local_cpu();
		static Vector<CPU::Data>& cpus();

		static void cpu_online();
		
	private:
		static Vector<CPU::Data> s_cpus;
		static uint16_t s_cpus_online;
		static Spinlock s_spinlock;
	};
} // namespace Kernel
