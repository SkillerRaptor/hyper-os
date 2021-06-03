#pragma once

#include <Kernel/Boot/Stivale.hpp>

namespace Kernel
{
	class SMP
	{
	public:
		static void initialize(stivale2_struct_tag_smp* smp_tag);
	
	private:
		static uint32_t s_bsp_lapic_id;
	};
}

__attribute__((noreturn)) void cpu_init();
