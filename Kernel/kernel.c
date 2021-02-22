#include <sys/cdefs.h>
#include <AK/logger.h>
#include <AK/serial.h>
#include <Kernel/Boot/stivale2.h>
#include <Kernel/Core/gdt.h>
#include <Kernel/Interrupts/idt.h>
#include <Kernel/Interrupts/irq.h>
#include <Kernel/Interrupts/pic.h>

void kernel_main(struct stivale2_struct* bootloader_data)
{
	(void)bootloader_data;

	gdt_init();

	pic_remap(0x20, 0x28);

	irq_init();
	idt_init();
	
	serial_init();

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