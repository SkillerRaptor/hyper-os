#include <Kernel/Boot/Stivale.hpp>
#include <Kernel/Memory/PhysicalMemoryManager.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/IDT.hpp>
#include <Kernel/System/PIC.hpp>
#include <stddef.h>

namespace Kernel
{
	using ConstructorFunction = void (*)();
	ConstructorFunction constructors_start;
	ConstructorFunction constructors_end;
	
	extern "C" __attribute__((noreturn)) void main(stivale2_struct* bootloader_data)
	{
		GDT::initialize();
		PIC::remap(0x20, 0x28);
		IDT::initialize();
		
		auto* framebuffer_tag = reinterpret_cast<stivale2_struct_tag_framebuffer*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID));
		
		auto* screen = reinterpret_cast<uint8_t*>(framebuffer_tag->framebuffer_addr);
		for (size_t y = 0; y < framebuffer_tag->framebuffer_height; ++y)
		{
			const size_t screen_position_y = y * framebuffer_tag->framebuffer_pitch;
			for (size_t x = 0; x < framebuffer_tag->framebuffer_width; ++x)
			{
				const size_t screen_position_x = x * (framebuffer_tag->framebuffer_bpp / 8);
				screen[screen_position_x + screen_position_y + 0] = 0;
				screen[screen_position_x + screen_position_y + 1] = 255;
				screen[screen_position_x + screen_position_y + 2] = 255;
			}
		}
		
		auto* memory_map_tag = reinterpret_cast<stivale2_struct_tag_memmap*>(stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID));
		PhysicalMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);
		VirtualMemoryManager::initialize(memory_map_tag->memmap, memory_map_tag->entries);
		
		for (ConstructorFunction* constructor = &constructors_start; constructor < &constructors_end; ++constructor)
		{
			(*constructor)();
		}
		
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
		
		while (true)
		{
			asm volatile ("hlt");
		}
	}
}
