#include <AK/Logger.hpp>
#include <AK/Memory.hpp>
#include <AK/Serial.hpp>
#include <Kernel/Boot/Stivale.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/System/ACPI.hpp>
#include <Kernel/System/APIC.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/HPET.hpp>
#include <Kernel/System/IDT.hpp>
#include <Kernel/System/PIC.hpp>
#include <Kernel/System/SMP.hpp>
#include <stddef.h>

namespace Kernel
{
	using ConstructorFunction = void (*)();
	extern "C" ConstructorFunction constructors_start[];
	extern "C" ConstructorFunction constructors_end[];
	
	extern "C" __attribute__((noreturn)) void main(stivale2_struct* bootloader_data)
	{
		AK::Serial::initialize();
		
		auto* firmware_tag = reinterpret_cast<stivale2_struct_tag_firmware*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_FIRMWARE_ID));
		AK::Logger::info(" _  _                     ___  ___    ");
		AK::Logger::info("| || |_  _ _ __  ___ _ _ / _ \\/ __|  ");
		AK::Logger::info("| __ | || | '_ \\/ -_) '_| (_) \\__ \\");
		AK::Logger::info("|_||_|\\_, | .__/\\___|_|  \\___/|___/");
		AK::Logger::info("      |__/|_|                         ");
		AK::Logger::info("");
		AK::Logger::info("Firmware: %s", (firmware_tag->flags & STIVALE2_FIRMWARE_BIOS) ? "BIOS" : "UEFI");
		AK::Logger::info("Bootloader: %s %s", bootloader_data->bootloader_brand, bootloader_data->bootloader_version);
		AK::Logger::info("");
		AK::Logger::info("------------------------------------");
		AK::Logger::info("");
		
		AK::Logger::info("HyperOS is booting...");
		
		GDT::initialize();
		PIC::remap(0x20, 0x28);
		IDT::initialize();
		
		auto* memory_map_tag = reinterpret_cast<stivale2_struct_tag_memmap*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID));
		PhysicalMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);
		VirtualMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);
		
		for (ConstructorFunction* constructor = constructors_start; constructor < constructors_end; ++constructor)
		{
			(*constructor)();
		}
		
		auto* rsdp_tag = reinterpret_cast<stivale2_struct_tag_rsdp*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_RSDP_ID));
		ACPI::initialize(reinterpret_cast<ACPI::RSDP*>(rsdp_tag->rsdp + AK::s_physical_memory_offset));
		APIC::initialize();
		HPET::initialize();
		
		auto* smp_tag = reinterpret_cast<stivale2_struct_tag_smp*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_SMP_ID));
		SMP::initialize(smp_tag);
		
		auto* framebuffer_tag = reinterpret_cast<stivale2_struct_tag_framebuffer*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID));
		auto* screen = reinterpret_cast<uint8_t*>(framebuffer_tag->framebuffer_addr);
		for (size_t y = 0; y < framebuffer_tag->framebuffer_height; ++y)
		{
			const size_t screen_position_y = y * framebuffer_tag->framebuffer_pitch;
			for (size_t x = 0; x < framebuffer_tag->framebuffer_width; ++x)
			{
				const size_t screen_position_x = x * (framebuffer_tag->framebuffer_bpp / 8);
				screen[screen_position_x + screen_position_y + 0] = 255;
				screen[screen_position_x + screen_position_y + 1] = 0;
				screen[screen_position_x + screen_position_y + 2] = 255;
			}
		}
		
		asm volatile("sti");
		
		AK::Logger::info("HyperOS booted successfully!");
		
		while (true)
		{
			asm volatile ("hlt");
		}
	}
}
