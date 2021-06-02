#pragma once

#include <stdint.h>

namespace AK
{
	class IoService
	{
	public:
		static void outb(uint16_t port, uint8_t value);
		static uint8_t inb(uint16_t port);
		
		static void wait();
	};
}
