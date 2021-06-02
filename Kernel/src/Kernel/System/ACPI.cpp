#include <AK/Memory.hpp>
#include <AK/Logger.hpp>
#include <Kernel/System/Stdlib.hpp>
#include <Kernel/System/ACPI.hpp>
#include <Kernel/System/MADT.hpp>

namespace Kernel
{
	bool ACPI::s_use_xsdt{ false };
	ACPI::RSDT* ACPI::s_rsdt{ nullptr };
	
	void ACPI::initialize(ACPI::RSDP* rsdp)
	{
		AK::Logger::info("ACPI: Initializing...");
		
		ACPI::detect_rsdt(rsdp);
		MADT::initialize();
		
		AK::Logger::info("ACPI: Initializing finished!");
	}
	
	void* ACPI::find_sdt(const char* signature, size_t index)
	{
		size_t count = 0;
		for (size_t i = 0; i < s_rsdt->sdt.length - sizeof(ACPI::SDT); ++i)
		{
			ACPI::SDT* ptr = get_sdt(i);
			
			if(!strncmp(ptr->signature, signature, 4) && (count++ == index))
			{
				AK::Logger::debug("ACPI: Found '%s' at %x", signature, ptr);
				return reinterpret_cast<void*>(ptr);
			}
		}
		
		AK::Logger::error("ACPI: '%s' not found!", signature);
		return nullptr;
	}
	
	void ACPI::detect_rsdt(ACPI::RSDP* rsdp)
	{
		if (rsdp->revision < 2 && !rsdp->xsdt_address)
		{
			s_use_xsdt = false;
			s_rsdt = reinterpret_cast<ACPI::RSDT*>(rsdp->rsdt_address + AK::s_physical_memory_offset);
			AK::Logger::debug("ACPI: Found RSDT at %x", reinterpret_cast<uintptr_t>(s_rsdt));
			return;
		}
		
		s_use_xsdt = true;
		s_rsdt = reinterpret_cast<ACPI::RSDT*>(rsdp->xsdt_address + AK::s_physical_memory_offset);
		AK::Logger::debug("ACPI: Found XSDT at %x", reinterpret_cast<uintptr_t>(s_rsdt));
	}
	
	ACPI::SDT* ACPI::get_sdt(size_t index)
	{
		if (!s_use_xsdt)
		{
			auto* current_pointer = reinterpret_cast<uint32_t*>(s_rsdt->pointer_start);
			return reinterpret_cast<ACPI::SDT*>(current_pointer[index] + AK::s_physical_memory_offset);
		}
		
		auto* current_pointer = reinterpret_cast<uint64_t*>(s_rsdt->pointer_start);
		return reinterpret_cast<ACPI::SDT*>(current_pointer[index] + AK::s_physical_memory_offset);
	}
}
