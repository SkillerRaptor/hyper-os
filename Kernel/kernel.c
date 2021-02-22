#include <sys/cdefs.h>
#include <AK/logger.h>
#include <AK/serial.h>
#include <Kernel/Boot/stivale2.h>
#include <Kernel/Core/gdt.h>
#include <Kernel/Interrupts/idt.h>
#include <Kernel/Interrupts/irq.h>
#include <Kernel/Interrupts/pic.h>
#include <Kernel/Memory/mm.h>
#include <Kernel/Memory/pmm.h>
#include <Kernel/Memory/vmm.h>

void kernel_main(struct stivale2_struct* bootloader_data)
{
	bootloader_data = (struct stivale2_struct*)((void*)((uint64_t)bootloader_data + KERNEL_BASE_ADDRESS));

	gdt_init();

	pic_remap(0x20, 0x28);

	irq_init();
	idt_init();
	
	serial_init();

	struct stivale2_struct_tag_memmap* memmapTag = (struct stivale2_struct_tag_memmap*)stivale2_get_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID);

	pmm_init(memmapTag->memmap, memmapTag->entries);
	vmm_init(memmapTag->memmap, memmapTag->entries);

	pic_set_interrupt_request_mask(0);

    asm volatile (
        "sti"
        );

	while (1)
	{
    	asm volatile (
        	"hlt"
        	);
	}
}