#include <AK/Logger.hpp>
#include <AK/Memory.hpp>
#include <Kernel/System/HPET.hpp>

namespace Kernel
{
	HPET::Table* HPET::s_table{ nullptr };
	HPET::Entry* HPET::s_entry{ nullptr };
	
	uint64_t HPET::s_ticks{ 0 };
	
	void HPET::initialize()
	{
		AK::Logger::info("HPET: Initializing...");
		
		s_table = reinterpret_cast<HPET::Table*>(ACPI::find_sdt("HPET", 0));
		s_entry = reinterpret_cast<HPET::Entry*>(s_table->address_space_id + AK::s_physical_memory_offset);
		
		uint64_t clock_period = s_entry->general_capabilities >> 32;
		uint64_t frequency = 1000000000000000 / clock_period;
		
		AK::Logger::debug("HPET: Frequency - %u", frequency);
		
		if (!(s_entry->general_capabilities & s_general_legacy_replacement))
		{
			AK::Logger::error("HPET: Not legacy replacement capable!");
			return;
		}
		
		HPET::Timer* first_timer = &s_entry->timers[0];
		if (!(first_timer->configuration & static_cast<uint8_t>(HPET::TimerConfiguration::PeriodicModeSupport)))
		{
			AK::Logger::error("HPET: Periodic Mode not supported!");
			return;
		}
		
		first_timer->configuration |= static_cast<uint8_t>(HPET::TimerConfiguration::EnableInterrupt);
		first_timer->configuration |= static_cast<uint8_t>(HPET::TimerConfiguration::EnablePeriodicMode);
		first_timer->configuration |= static_cast<uint8_t>(HPET::TimerConfiguration::SetPeriodicAccumulator);
		first_timer->compare_value = frequency / 1000;
		
		s_entry->general_configuration |= 0x01;
		
		s_entry->general_configuration |= 0x10;
		s_entry->main_counter_value = 0;
		
		AK::Logger::info("HPET: Initializing finished!");
	}
	
	void HPET::sleep(uint64_t milliseconds)
	{
		uint64_t current_ticks = s_ticks;
		while (true)
		{
			if (current_ticks + milliseconds < s_ticks)
			{
				break;
			}
		}
	}
	
	void HPET::tick()
	{
		s_ticks++;
	}
	
	uint64_t HPET::ticks()
	{
		return s_ticks;
	}
}
