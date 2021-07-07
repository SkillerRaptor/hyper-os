/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/main.hpp>
#include <Kernel/Arch/Stivale.hpp>
#include <Kernel/Common/Logger.hpp>
#include <Kernel/Common/Memory.hpp>
#include <Kernel/Common/Serial.hpp>
#include <Kernel/Drivers/HPET.hpp>
#include <Kernel/Interrupts/APIC.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/Interrupts/PIC.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/Scheduling/Scheduler.hpp>
#include <Kernel/System/ACPI.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/SMP.hpp>

namespace Kernel
{
	using ConstructorFunction = void (*)();
	extern "C" ConstructorFunction constructors_start[];
	extern "C" ConstructorFunction constructors_end[];
	
	void kernel_main(stivale2_struct* bootloader_data)
	{
		Serial::initialize();

		auto* firmware_tag = reinterpret_cast<stivale2_struct_tag_firmware*>(
			stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_FIRMWARE_ID));

		Logger::info(" _  _                     ___  ___    ");
		Logger::info("| || |_  _ _ __  ___ _ _ / _ \\/ __|  ");
		Logger::info("| __ | || | '_ \\/ -_) '_| (_) \\__ \\");
		Logger::info("|_||_|\\_, | .__/\\___|_|  \\___/|___/");
		Logger::info("      |__/|_|                         ");
		Logger::info("");
		Logger::info("Firmware: %s", (firmware_tag->flags & STIVALE2_FIRMWARE_BIOS) ? "BIOS" : "UEFI");
		Logger::info("Bootloader: %s %s", bootloader_data->bootloader_brand, bootloader_data->bootloader_version);
		Logger::info("");
		Logger::info("------------------------------------");
		Logger::info("");

		Logger::info("HyperOS is booting...");

		GDT::initialize();
		PIC::remap(0x20, 0x28);
		IDT::initialize();

		auto* memory_map_tag = reinterpret_cast<stivale2_struct_tag_memmap*>(
			stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID));
		PhysicalMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);
		VirtualMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);

		for (ConstructorFunction* constructor = constructors_start; constructor < constructors_end; ++constructor)
		{
			(*constructor)();
		}

		auto* rsdp_tag =
			reinterpret_cast<stivale2_struct_tag_rsdp*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_RSDP_ID));

		ACPI::initialize(reinterpret_cast<ACPI::RSDP*>(rsdp_tag->rsdp + s_physical_memory_offset));
		APIC::initialize();
		HPET::initialize();
		
		APIC::calibrate(100);

		auto* smp_tag =
			reinterpret_cast<stivale2_struct_tag_smp*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_SMP_ID));

		SMP::initialize(smp_tag);
		Scheduler::initialize();
		
		pid_t pid = Scheduler::create_task(-1, nullptr);
		Scheduler::create_thread(pid, reinterpret_cast<uint64_t>(kernel_thread), 0x8);
		
		Logger::info("HyperOS booted successfully!");

		__asm__ __volatile__("sti");

		while (true)
		{
			__asm__ __volatile__("hlt");
		}
	}
	
	void kernel_thread()
	{
		Logger::error("Kernel thread works! :^)");
		
		while (true)
		{
			__asm__ __volatile__("hlt");
		}
	}
} // namespace Kernel
