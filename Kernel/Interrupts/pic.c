#include <Kernel/Interrupts/pic.h>

#include <AK/io.h>
#include <AK/logger.h>

#define IN_SERVICE_REGISTER_CODE 0x0A
#define INTERRUPT_REQUEST_REGISTER_CODE 0x0B
#define DISABLE_CODE 0xFF
#define END_OF_INTERRUPT_CODE 0x20

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW1_8086 0x01

void pic_remap(uint8_t master_offset, uint8_t slave_offset)
{
	info("Kernel (pic.c): Remapping PIC...");

	/* Start Initialization Sequence */
	io_outb(MASTER_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);
	io_wait();
	io_outb(SLAVE_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);
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
	io_outb(MASTER_DATA_SELECTOR, ICW1_8086);
	io_wait();
	io_outb(SLAVE_DATA_SELECTOR, ICW1_8086);
	io_wait();

	info("Kernel (pic.c): PIC remaped!");
}

void pic_disable(void)
{
	io_outb(SLAVE_DATA_SELECTOR, DISABLE_CODE);
	io_outb(MASTER_DATA_SELECTOR, DISABLE_CODE);
}

void pic_send_end_of_interrupt(uint8_t interrupt_request_line)
{
	if (interrupt_request_line >= 0x8)
		io_outb(SLAVE_COMMAND_SELECTOR, END_OF_INTERRUPT_CODE);
	io_outb(MASTER_COMMAND_SELECTOR, END_OF_INTERRUPT_CODE);
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
    io_outb(MASTER_COMMAND_SELECTOR, IN_SERVICE_REGISTER_CODE);
    io_outb(SLAVE_COMMAND_SELECTOR, IN_SERVICE_REGISTER_CODE);
    return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}

uint16_t pic_get_interrupt_request_register(void)
{
    io_outb(MASTER_COMMAND_SELECTOR, INTERRUPT_REQUEST_REGISTER_CODE);
    io_outb(SLAVE_COMMAND_SELECTOR, INTERRUPT_REQUEST_REGISTER_CODE);
    return (io_inb(SLAVE_COMMAND_SELECTOR) << 8) | io_inb(MASTER_COMMAND_SELECTOR);
}
