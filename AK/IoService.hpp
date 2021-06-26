#pragma once

#include <stdint.h>

namespace AK
{
	class IoService
	{
	public:
		static void outb(uint16_t port, uint8_t value);
		static uint8_t inb(uint16_t port);
		
		static void outw(uint16_t port, uint16_t value);
		static uint16_t inw(uint16_t port);
		
		static void outl(uint16_t port, uint32_t value);
		static uint32_t inl(uint16_t port);
		
		static void wait();
	};
}
