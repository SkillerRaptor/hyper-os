#pragma once

#include <stdint.h>

class IO
{
public:
	static void out8(uint16_t port, uint8_t value);
	static uint8_t in8(uint16_t port);

	static void wait();
};