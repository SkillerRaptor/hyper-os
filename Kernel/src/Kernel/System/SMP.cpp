#include <AK/Assertion.hpp>
#include <AK/Memory.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/System/MADT.hpp>
#include <Kernel/System/SMP.hpp>

namespace Kernel
{
	AK::Vector<CPU::LocalData> SMP::s_cpus{};
	
	void SMP::initialize(stivale2_struct_tag_smp* smp_tag)
	{
		AK::Logger::info("SMP: Initializing...");
		
		AK::Logger::debug("SMP: BSP LAPIC id - %x", smp_tag->bsp_lapic_id);
		AK::Logger::debug("SMP: Total CPU count - %u", smp_tag->cpu_count);
		
		s_cpus.reserve(smp_tag->cpu_count);
		for (size_t i = 0; i < smp_tag->cpu_count; ++i)
		{
			AK::Logger::debug("SMP: Loading processor - %u", MADT::lapics()[i]->processor_id);
			s_cpus[i].lapic_id = MADT::lapics()[i]->apic_id;
			
			smp_tag->smp_info[i].extra_argument = 0;
			
			if (smp_tag->smp_info[i].lapic_id == smp_tag->bsp_lapic_id)
			{
				continue;
			}
			
			auto stack = reinterpret_cast<uintptr_t>(PhysicalMemoryManager::callocate(1)) + AK::s_physical_memory_offset;
			
			smp_tag->smp_info[i].target_stack = stack;
			smp_tag->smp_info[i].goto_address = reinterpret_cast<uint64_t>(CPU::initialize);
		}
		
		AK::Logger::info("SMP: Initializing finished!");
	}
	
	AK::Vector<CPU::LocalData>& SMP::cpus()
	{
		return s_cpus;
	}
}
