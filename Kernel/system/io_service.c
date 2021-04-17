#include "io_service.h"

#define IO_WAIT_PORT 0x80

void io_outb(uint16_t port, uint8_t value)
{
	asm volatile (
	"outb %0, %1"
	:
	: "a"(value), "Nd"(port)
	);
}

uint8_t io_inb(uint16_t port)
{
	uint8_t ret;
	asm volatile (
	"inb %1, %0"
	: "=a"(ret) : "Nd"(port)
	);
	return ret;
}

void io_wait(void)
{
	io_outb(IO_WAIT_PORT, 0x0);
}