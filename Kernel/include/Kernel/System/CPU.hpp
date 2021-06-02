#pragma once

#include <Kernel/Boot/Stivale.hpp>
#include <stdint.h>

namespace Kernel
{
	class CPU
	{
	public:
		static void initialize(stivale2_smp_info* smp_info);
		
		static uint64_t read_timestamp();
		static void invalidate_page(void* m);
		
		static void write_msr(uint64_t msr, uint64_t value);
		static uint64_t read_msr(uint64_t msr);
	};
}
