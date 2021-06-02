#include <AK/IoService.hpp>

namespace AK
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
	
	void IoService::outw(uint16_t port, uint16_t value)
	{
		asm volatile (
		"outw %0, %1"
		:
		: "a"(value), "Nd"(port)
		);
	}
	
	uint16_t IoService::inw(uint16_t port)
	{
		uint16_t return_value = 0;
		
		asm volatile (
		"inw %1, %0"
		: "=a"(return_value) : "Nd"(port)
		);
		
		return return_value;
	}
	
	void IoService::outl(uint16_t port, uint32_t value)
	{
		asm volatile (
		"outl %0, %1"
		:
		: "a"(value), "Nd"(port)
		);
	}
	
	uint32_t IoService::inl(uint16_t port)
	{
		uint32_t return_value = 0;
		
		asm volatile (
		"inl %1, %0"
		: "=a"(return_value) : "Nd"(port)
		);
		
		return return_value;
	}
	
	void IoService::wait()
	{
		IoService::outb(0x80, 0x00);
	}
}
