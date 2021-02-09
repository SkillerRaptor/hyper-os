#pragma once

#include <LibC/stdint.h>

namespace AK
{
	class IO
	{
	public:
		static void out8(uint16_t port, uint8_t value);
		static void out16(uint16_t port, uint16_t value);

		static uint8_t in8(uint16_t port);
		static uint16_t in16(uint16_t port);

		static void io_wait();
	};
}