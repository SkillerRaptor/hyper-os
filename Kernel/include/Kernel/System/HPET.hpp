#pragma once

#include <Kernel/System/ACPI.hpp>

namespace Kernel
{
	class HPET
	{
	private:
		static constexpr const uint16_t s_general_legacy_replacement{ 1 << 15 };
		
		enum class TimerConfiguration : uint8_t
		{
			EnableInterrupt = 1 << 2,
			EnablePeriodicMode = 1 << 3,
			PeriodicModeSupport = 1 << 4,
			Size = 1 << 5,
			SetPeriodicAccumulator = 1 << 6
		};
		
		struct Table
		{
			ACPI::SDT sdt;
			uint8_t hardware_revision_id;
			uint8_t comparator_count : 5;
			uint8_t counter_size : 1;
			uint8_t reserved : 1;
			uint8_t legacy_replacement : 1;
			uint16_t pci_vendor_id;
			uint8_t address_space_id;
			uint8_t register_bit_width;
			uint8_t register_bit_offset;
			uint64_t address;
			uint8_t hpet_number;
			uint16_t minimum_tick;
			uint8_t page_protection;
		} __attribute__((packed));
		
		struct Timer
		{
			uint64_t configuration;
			uint64_t compare_value;
			uint64_t interrupt_route;
			uint64_t reserved;
		} __attribute__((packed));
		
		struct Entry
		{
			uint64_t general_capabilities;
			uint64_t reserved_0;
			uint64_t general_configuration;
			uint64_t reserved_1;
			uint64_t general_interrupt_status;
			uint64_t reserved_2;
			uint64_t reserved_3[2 * 12];
			uint64_t main_counter_value;
			uint64_t reserved_4;
			Timer timers[];
		} __attribute__((packed));
	
	public:
		static void initialize();
		static void sleep(uint64_t milliseconds);
		
		static void tick();
		static uint64_t ticks();
	
	private:
		static Table* s_table;
		static Entry* s_entry;
		
		static uint64_t s_ticks;
	};
}
