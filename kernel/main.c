#include <stddef.h>

#include <boot/stivale2.h>
#include <drivers/pcspkr.h>
#include <drivers/ps2/ps2_keyboard.h>
#include <drivers/ps2/ps2_mouse.h>
#include <memory/kalloc.h>
#include <memory/pmm.h>
#include <memory/memory.h>
#include <memory/vmm.h>
#include <system/gdt.h>
#include <system/idt.h>
#include <system/pic.h>
#include <system/pit.h>
#include <utilities/builtins.h>
#include <utilities/logger.h>
#include <utilities/serial.h>

void main(struct stivale2_struct* stivale2_struct)
{
	stivale2_struct = (void*) stivale2_struct + PHYSICAL_MEMORY_OFFSET;
	
	serial_init();
	
	info("HyperOS is booting...");
	
	gdt_init();
	
	pic_remap(0x20, 0x28);
	idt_init();
	
	pit_init(100);
	
	struct stivale2_struct_tag_memory_map* memory_map_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MEMORY_MAP_ID);
	
	pmm_init(memory_map_tag->memory_map, memory_map_tag->entries);
	vmm_init(memory_map_tag->memory_map, memory_map_tag->entries);
	
	struct stivale2_struct_tag_framebuffer* framebuffer_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
	
	//<editor-fold desc="Testing memory">
	void* backbuffer = kmalloc(framebuffer_tag->framebuffer_height * framebuffer_tag->framebuffer_pitch);
	uint8_t* screen = (uint8_t*) backbuffer;
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
	
	memcpy((void*)framebuffer_tag->framebuffer_addr, (void*)backbuffer, framebuffer_tag->framebuffer_height * framebuffer_tag->framebuffer_pitch);
	kfree(backbuffer);
	//</editor-fold>
	
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