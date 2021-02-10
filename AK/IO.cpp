#include <AK/IO.h>

void IO::out8(uint16_t port, uint8_t value)
{
	asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
}

uint8_t IO::in8(uint16_t port)
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void IO::wait()
{
	out8(0x80, 0);
}