#include "pic.h"

#include "io_service.h"

#include <lib/logger.h>

void pic_remap(uint8_t master_offset, uint8_t slave_offset)
{
	info("PIC: Initializing...");
	
	/* Start Initialization Sequence */
	io_outb(MASTER_COMMAND_SELECTOR, 0x11);
	io_wait();
	io_outb(SLAVE_COMMAND_SELECTOR, 0x11);
	io_wait();
	
	/* Set PIC's vector offsets */
	io_outb(MASTER_DATA_SELECTOR, master_offset);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, slave_offset);
	io_wait();
	
	/* Set Identity */
	io_outb(MASTER_DATA_SELECTOR, 0x04);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, 0x02);
	io_wait();
	
	/* Set 8086 Mode */
	io_outb(MASTER_DATA_SELECTOR, 0x01);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, 0x01);
	io_wait();
	
	info("PIC: Initializing finished!");
}

void pic_disable(void)
{
	io_outb(SLAVE_DATA_SELECTOR, 0xFF);
	io_outb(MASTER_DATA_SELECTOR, 0xFF);
}

void pic_send_end_of_interrupt(uint8_t interrupt_request_line)
{
	if (interrupt_request_line >= 0x8)
	{
		io_outb(SLAVE_COMMAND_SELECTOR, 0x20);
	}
	io_outb(MASTER_COMMAND_SELECTOR, 0x20);
}

void pic_set_interrupt_request_mask(uint8_t interrupt_request_line)
{
	uint16_t port;
	
	if (interrupt_request_line < 0x8)
	{
		port = MASTER_DATA_SELECTOR;
	}
	else
	{
		port = SLAVE_DATA_SELECTOR;
		interrupt_request_line -= 0x8;
	}
	
	io_outb(port, io_inb(port) | (1 << interrupt_request_line));
}

void pic_clear_interrupt_request_mask(uint8_t interrupt_request_line)
{
	uint16_t port;
	
	if (interrupt_request_line < 0x8)
	{
		port = MASTER_DATA_SELECTOR;
	}
	else
	{
		port = SLAVE_DATA_SELECTOR;
		interrupt_request_line -= 0x8;
	}
	
	io_outb(port, io_inb(port) & ~(1 << interrupt_request_line));
}

uint16_t pic_get_in_service_register(void)
{
	io_outb(MASTER_COMMAND_SELECTOR, 0x0A);
	io_outb(SLAVE_COMMAND_SELECTOR, 0x0A);
	return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}

uint16_t pic_get_interrupt_request_register(void)
{
	io_outb(MASTER_COMMAND_SELECTOR, 0x0B);
	io_outb(SLAVE_COMMAND_SELECTOR, 0x0B);
	return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}
