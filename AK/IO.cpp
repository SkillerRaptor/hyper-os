#include <AK/IO.h>

namespace AK
{
	void IO::out8(uint16_t port, uint8_t value)
	{
		asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
	}

	void IO::out16(uint16_t port, uint16_t value)
	{
		asm volatile("outw %0, %1" :: "a"(value), "Nd"(port));
	}

	uint8_t IO::in8(uint16_t port)
	{
		uint8_t ret;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	uint16_t IO::in16(uint16_t port)
	{
		uint16_t ret;
		asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
		return ret;
	}

	void IO::io_wait()
	{
		out8(0x80, 0);
	}
}