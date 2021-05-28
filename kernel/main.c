#include <stddef.h>

#include <boot/stivale2.h>
#include <drivers/pcspkr.h>
#include <drivers/ps2/ps2_keyboard.h>
#include <drivers/ps2/ps2_mouse.h>
#include <memory/kalloc.h>
#include <memory/pmm.h>
#include <memory/memory.h>
#include <memory/vmm.h>
//#include <system/apic.h>
#include <system/gdt.h>
#include <system/idt.h>
//#include <system/pci.h>
#include <system/pic.h>
#include <system/pit.h>
//#include <system/smp.h>
#include <lib/builtins.h>
#include <lib/logger.h>
#include <lib/serial.h>

__attribute__((noreturn)) void main(struct stivale2_struct* stivale2_struct)
{
	stivale2_struct = (void*) stivale2_struct + PHYSICAL_MEMORY_OFFSET;
	
	serial_init();
	
	info("HyperOS is booting...");
	
	gdt_init();
	
	pic_remap(0x20, 0x28);
	//apic_init();
	idt_init();
	
	//pci_init();
	
	pit_init(100);
	
	struct stivale2_struct_tag_memmap* memory_map_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);
	
	pmm_init(memory_map_tag->memmap, memory_map_tag->entries);
	vmm_init(memory_map_tag->memmap, memory_map_tag->entries);
	
	//struct stivale2_struct_tag_smp* smp_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_SMP_ID);
	//smp_init(smp_tag);
	
	struct stivale2_struct_tag_framebuffer* framebuffer_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
	
	void* backbuffer = kmalloc(framebuffer_tag->framebuffer_height * framebuffer_tag->framebuffer_pitch);
	
	uint8_t* screen = (uint8_t*) backbuffer;
	for (size_t y = 0; y < framebuffer_tag->framebuffer_height; ++y)
	{
		const size_t screen_position_y = y * framebuffer_tag->framebuffer_pitch;
		for (size_t x = 0; x < framebuffer_tag->framebuffer_width; ++x)
		{
			const size_t screen_position_x = x * (framebuffer_tag->framebuffer_bpp / 8);
			screen[screen_position_x + screen_position_y + 0] = 50;
			screen[screen_position_x + screen_position_y + 1] = 50;
			screen[screen_position_x + screen_position_y + 2] = 50;
		}
	}
	
	uint32_t rect_x = 100;
	uint32_t rect_y = 100;
	uint32_t rect_width = 500;
	uint32_t rect_height = 300;
	
	for (size_t y = rect_y; y < rect_y + rect_height; ++y)
	{
		const size_t screen_position_y = y * framebuffer_tag->framebuffer_pitch;
		for (size_t x = rect_x; x < rect_x + rect_width; ++x)
		{
			const size_t screen_position_x = x * (framebuffer_tag->framebuffer_bpp / 8);
			screen[screen_position_x + screen_position_y + 0] = 0x66;
			screen[screen_position_x + screen_position_y + 1] = 0x66;
			screen[screen_position_x + screen_position_y + 2] = 0x66;
		}
	}
	
	for (size_t y = rect_y + 5; y < rect_y + rect_height - 5; ++y)
	{
		const size_t screen_position_y = y * framebuffer_tag->framebuffer_pitch;
		for (size_t x = rect_x + 5; x < rect_x + rect_width - 5; ++x)
		{
			const size_t screen_position_x = x * (framebuffer_tag->framebuffer_bpp / 8);
			screen[screen_position_x + screen_position_y + 0] = 0xBB;
			screen[screen_position_x + screen_position_y + 1] = 0xBB;
			screen[screen_position_x + screen_position_y + 2] = 0xBB;
		}
	}
	
	memcpy((void*) framebuffer_tag->framebuffer_addr, (void*) backbuffer, framebuffer_tag->framebuffer_height * framebuffer_tag->framebuffer_pitch);
	kfree(backbuffer);
	
	ps2_keyboard_init();
	ps2_mouse_init();
	pcspkr_init();
	
	info("HyperOS booted successful!");
	
	asm volatile ("sti");
	
	pcspkr_beep(500);
	
	for (;;)
	{
		asm volatile ("hlt");
	}
}
