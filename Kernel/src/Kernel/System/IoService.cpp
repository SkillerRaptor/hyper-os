#include <Kernel/System/IoService.hpp>

namespace Kernel
{
	void IoService::outb(uint16_t port, uint8_t value)
	{
		asm volatile (
		"outb %0, %1"
		:
		: "a"(value), "Nd"(port)
		);
	}
	
	uint8_t IoService::inb(uint16_t port)
	{
		uint8_t return_value = 0;
		
		asm volatile (
		"inb %1, %0"
		: "=a"(return_value) : "Nd"(port)
		);
		
		return return_value;
	}
	
	void IoService::wait()
	{
		IoService::outb(0x80, 0x00);
	}
}
