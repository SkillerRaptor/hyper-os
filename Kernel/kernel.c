#include <sys/cdefs.h>
#include <AK/logger.h>
#include <AK/serial.h>
#include <Kernel/Boot/stivale2.h>
#include <Kernel/Core/gdt.h>
#include <Kernel/Interrupts/idt.h>
#include <Kernel/Interrupts/irq.h>
#include <Kernel/Interrupts/pic.h>
#include <Kernel/Memory/kmm.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/pmm.h>
#include <Kernel/Memory/vmm.h>
#include <LibGUI/painter.h>

void kernel_main(struct stivale2_struct* bootloader_data)
{
	bootloader_data = (void*)bootloader_data + PHYSICAL_MEMORY_OFFSET;

	gdt_init();

	pic_remap(0x20, 0x28);

	irq_init();
	idt_init();

	serial_init();

	struct stivale2_struct_tag_memmap* memmap_tag = (struct stivale2_struct_tag_memmap*)stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID);
	
	pmm_init(memmap_tag->memmap, memmap_tag->entries);
	vmm_init(memmap_tag->memmap, memmap_tag->entries);

	pic_set_interrupt_request_mask(0);

	struct stivale2_struct_tag_framebuffer* framebuffer_tag = (struct stivale2_struct_tag_framebuffer*)stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
	
	return;
	
	painter_init(framebuffer_tag);

	asm volatile (
		"sti"
		);
	
	color_t color;
	color.red = 255;
	color.green = 0;
	color.blue = 255;
	
	painter_clear(color);

	while (1)
	{
		asm volatile (
			"hlt"
			);
	}
}