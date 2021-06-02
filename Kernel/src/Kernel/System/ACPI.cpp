#include <AK/Memory.hpp>
#include <AK/Logger.hpp>
#include <Kernel/System/ACPI.hpp>

namespace Kernel
{
	bool ACPI::s_use_xsdt{ false };
	ACPI::RSDT* ACPI::s_rsdt{ nullptr };
	
	void ACPI::initialize(ACPI::RSDP* rsdp)
	{
		AK::Logger::info("ACPI: Initializing...");
		
		ACPI::detect_rsdt(rsdp);
		
		AK::Logger::info("ACPI: Initializing finished!");
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
}
