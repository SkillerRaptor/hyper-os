#pragma once

#include <AK/Vector.hpp>
#include <Kernel/Boot/Stivale.hpp>
#include <Kernel/System/CPU.hpp>

namespace Kernel
{
	class SMP
	{
	public:
		static void initialize(stivale2_struct_tag_smp* smp_tag);
	
		static AK::Vector<CPU::LocalData>& cpus();
		
	private:
		static AK::Vector<CPU::LocalData> s_cpus;
	};
}

__attribute__((noreturn)) void cpu_init();
