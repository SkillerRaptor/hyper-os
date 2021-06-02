#pragma once

#include <stdint.h>

namespace Kernel
{
	class GDT
	{
	public:
		static constexpr const uint8_t s_kernel_code_selector{ 0x08 };
		static constexpr const uint8_t s_kernel_data_selector{ 0x10 };
	
	private:
		enum class AccessAttribute : uint8_t
		{
			Null = 0 << 0,
			Ring0 = 0 << 0,
			Task = 0 << 0,
			Present = 1 << 7,
			Ring3 = 1 << 5 | 1 << 6,
			CodeOrData = 1 << 4,
			Executable = 1 << 3,
			GrowsDown = 1 << 2,
			AllowLower = 1 << 2,
			Readable = 1 << 1,
			Writeable = 1 << 1,
			Tss = 1 << 0,
		};
		
		enum class FlagAttribute : uint8_t
		{
			Null = 0 << 0,
			Granularity1B = 0 << 0,
			Granularity4K = 1 << 3,
			Mode16Bit = 0 << 0,
			Mode32Bit = 1 << 2,
			Mode64Bit = 1 << 1
		};
		
		struct Entry
		{
			uint16_t limit_low;
			uint16_t base_low;
			uint8_t base_middle;
			uint8_t access;
			uint8_t limit_high : 4;
			uint8_t flags : 4;
			uint8_t base_high;
		} __attribute__((packed));
		
		struct Entries
		{
			Entry null_entry;
			Entry kernel_entries[2];
			Entry userland_entries[2];
			// TODO: Adding TSS Entry
		} __attribute__((packed));
		
		struct Pointer
		{
			uint16_t size;
			uint64_t address;
		} __attribute__((packed));
	
	public:
		static void initialize();
		static void reload();
	
	private:
		static void create_descriptor(Entry* entry, uint32_t base, uint32_t limit, AccessAttribute access, FlagAttribute flags);
	
		friend AccessAttribute operator|(const AccessAttribute& left, const AccessAttribute& right);
		friend FlagAttribute operator|(const FlagAttribute& left, const FlagAttribute& right);
	
	private:
		static Entries s_entries;
		static Pointer s_pointer;
	};
}
