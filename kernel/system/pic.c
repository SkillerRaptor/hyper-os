#include "pic.h"

#include "io_service.h"

#include <lib/logger.h>

#define PIC_ICW1_ICW4 (1 << 0)
#define PIC_ICW1_INIT (1 << 4)
#define PIC_ICW1_8086 (1 << 0)

#define PIC_MASTER_IDENTITY 0x04
#define PIC_SLAVE_IDENTITY 0x02

#define PIC_IN_SERVICE_REGISTER_CODE 0x0A
#define PIC_INTERRUPT_REQUEST_REGISTER_CODE 0x0B
#define PIC_DISABLE_CODE 0xFF
#define PIC_END_OF_INTERRUPT_CODE 0x20

void pic_remap(uint8_t master_offset, uint8_t slave_offset)
{
	info("Remapping PIC...");
	
	/* Start Initialization Sequence */
	io_outb(MASTER_COMMAND_SELECTOR, PIC_ICW1_INIT | PIC_ICW1_ICW4);
	io_wait();
	io_outb(SLAVE_COMMAND_SELECTOR, PIC_ICW1_INIT | PIC_ICW1_ICW4);
	io_wait();
	info(" The initialization sequence was started!");
	
	/* Set PIC's vector offsets */
	io_outb(MASTER_DATA_SELECTOR, master_offset);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, slave_offset);
	io_wait();
	info(" The vector offsets was set!");
	
	/* Set Identity */
	io_outb(MASTER_DATA_SELECTOR, PIC_MASTER_IDENTITY);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, PIC_SLAVE_IDENTITY);
	io_wait();
	info(" The identity was set!");
	
	/* Set 8086 Mode */
	io_outb(MASTER_DATA_SELECTOR, PIC_ICW1_8086);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, PIC_ICW1_8086);
	io_wait();
	info(" The 8086 mode was set!");
	
	info("Remapping PIC finished!");
}

void pic_disable(void)
{
	io_outb(SLAVE_DATA_SELECTOR, PIC_DISABLE_CODE);
	io_outb(MASTER_DATA_SELECTOR, PIC_DISABLE_CODE);
}

void pic_send_end_of_interrupt(uint8_t interrupt_request_line)
{
	if (interrupt_request_line >= 0x8)
	{
		io_outb(SLAVE_COMMAND_SELECTOR, PIC_END_OF_INTERRUPT_CODE);
	}
	io_outb(MASTER_COMMAND_SELECTOR, PIC_END_OF_INTERRUPT_CODE);
}

void pic_set_interrupt_request_mask(uint8_t interrupt_request_line)
{
	uint16_t port;
	uint8_t value;
	
	if (interrupt_request_line < 0x8)
	{
		port = MASTER_DATA_SELECTOR;
	}
	else
	{
		port = SLAVE_DATA_SELECTOR;
		interrupt_request_line -= 0x8;
	}
	
	value = io_inb(port) | (1 << interrupt_request_line);
	io_outb(port, value);
}

void pic_clear_interrupt_request_mask(uint8_t interrupt_request_line)
{
	uint16_t port;
	uint8_t value;
	
	if (interrupt_request_line < 0x8)
	{
		port = MASTER_DATA_SELECTOR;
	}
	else
	{
		port = SLAVE_DATA_SELECTOR;
		interrupt_request_line -= 0x8;
	}
	
	value = io_inb(port) & ~(1 << interrupt_request_line);
	io_outb(port, value);
}

uint16_t pic_get_in_service_register(void)
{
	io_outb(MASTER_COMMAND_SELECTOR, PIC_IN_SERVICE_REGISTER_CODE);
	io_outb(SLAVE_COMMAND_SELECTOR, PIC_IN_SERVICE_REGISTER_CODE);
	return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}

uint16_t pic_get_interrupt_request_register(void)
{
	io_outb(MASTER_COMMAND_SELECTOR, PIC_INTERRUPT_REQUEST_REGISTER_CODE);
	io_outb(SLAVE_COMMAND_SELECTOR, PIC_INTERRUPT_REQUEST_REGISTER_CODE);
	return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}