#include <AK/Assertion.hpp>
#include <AK/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/System/CPU.hpp>
#include <Kernel/System/SMP.hpp>

namespace Kernel
{
	uint32_t SMP::s_bsp_lapic_id{ 0 };
	
	void SMP::initialize(stivale2_struct_tag_smp* smp_tag)
	{
		AK::Logger::info("SMP: Initializing...");
		
		AK::Logger::debug("SMP: BSP LAPIC id - %x", smp_tag->bsp_lapic_id);
		AK::Logger::debug("SMP: Total CPU count - %u", smp_tag->cpu_count);
		
		s_bsp_lapic_id = smp_tag->bsp_lapic_id;
		
		for (size_t i = 0; i < smp_tag->cpu_count; ++i)
		{
			smp_tag->smp_info[i].extra_argument = 0;
			
			if (smp_tag->smp_info[i].lapic_id == s_bsp_lapic_id)
			{
				continue;
			}
			
			auto stack = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(1)) + AK::s_physical_memory_offset;
			
			smp_tag->smp_info[i].target_stack = stack;
			smp_tag->smp_info[i].goto_address = reinterpret_cast<uint64_t>(CPU::initialize);
		}
		
		AK::Logger::info("SMP: Initializing finished!");
	}
}
