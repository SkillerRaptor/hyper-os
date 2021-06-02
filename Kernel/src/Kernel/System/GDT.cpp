#include <Kernel/System/GDT.hpp>

namespace Kernel
{
	GDT::Entries GDT::s_entries{};
	GDT::Pointer GDT::s_pointer{};
	
	void GDT::initialize()
	{
		GDT::create_descriptor(
			&s_entries.null_entry,
			0x00000000,
			0x00000000,
			AccessAttribute::Null,
			FlagAttribute::Null);
		
		GDT::create_descriptor(
			&s_entries.kernel_entries[0],
			0x00000000,
			0xFFFFFFFF,
			AccessAttribute::Present | AccessAttribute::CodeOrData | AccessAttribute::Executable | AccessAttribute::Readable,
			FlagAttribute::Granularity4K | FlagAttribute::Mode64Bit);
		
		GDT::create_descriptor(
			&s_entries.kernel_entries[1],
			0x00000000,
			0xFFFFFFFF,
			AccessAttribute::Present | AccessAttribute::CodeOrData | AccessAttribute::Writeable,
			FlagAttribute::Granularity4K | FlagAttribute::Mode32Bit);
		
		GDT::create_descriptor(
			&s_entries.userland_entries[0],
			0x00000000,
			0xFFFFFFFF,
			AccessAttribute::Present | AccessAttribute::CodeOrData | AccessAttribute::Executable | AccessAttribute::Readable | AccessAttribute::Ring3,
			FlagAttribute::Granularity4K | FlagAttribute::Mode64Bit);
		
		GDT::create_descriptor(
			&s_entries.userland_entries[1],
			0x00000000,
			0xFFFFFFFF,
			AccessAttribute::Present | AccessAttribute::CodeOrData | AccessAttribute::Writeable | AccessAttribute::Ring3,
			FlagAttribute::Granularity4K | FlagAttribute::Mode32Bit);
		
		s_pointer.size = sizeof(s_entries) - 1;
		s_pointer.address = reinterpret_cast<uintptr_t>(&s_entries);
		
		GDT::reload();
	}
	
	void GDT::reload()
	{
		asm volatile ("cli");
		
		asm volatile (
		"lgdt %0\n"
		"pushq %%rbp\n"
		"movq %%rsp, %%rbp\n"
		"pushq %1\n"
		"pushq %%rbp\n"
		"pushfq\n"
		"pushq %2\n"
		"pushq $1f\n"
		"iretq\n"
		"1:\n"
		"popq %%rbp\n"
		"mov %%ds, %1\n"
		"mov %%es, %1\n"
		"mov %%fs, %1\n"
		"mov %%gs, %1\n"
		"mov %%ss, %1\n"
		:
		: "m"(s_pointer), "r"(static_cast<uint64_t>(s_kernel_data_selector)), "r"(static_cast<uint64_t>(s_kernel_code_selector))
		: "memory"
		);
	}
	
	void GDT::create_descriptor(GDT::Entry* entry, uint32_t base, uint32_t limit, AccessAttribute access, FlagAttribute flags)
	{
		entry->base_low = base & 0x0000FFFF;
		entry->base_middle = (base & 0x00FF0000) >> 16;
		entry->base_high = (base & 0xFF000000) >> 24;
		
		entry->access = static_cast<uint8_t>(access);
		entry->flags = static_cast<uint8_t>(flags);
		
		entry->limit_low = limit & 0x0000FFFF;
		entry->limit_high = (limit & 0x000F0000) >> 16;
	}
	
	GDT::AccessAttribute operator|(const GDT::AccessAttribute& left, const GDT::AccessAttribute& right)
	{
		return static_cast<GDT::AccessAttribute>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
	}
	
	GDT::FlagAttribute operator|(const GDT::FlagAttribute& left, const GDT::FlagAttribute& right)
	{
		return static_cast<GDT::FlagAttribute>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
	}
}
