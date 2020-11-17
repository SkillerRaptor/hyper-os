#pragma once

#include <LibC/stdint.h>

class Color
{
private:
	uint32_t m_Value;

public:
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b);

	uint32_t GetValue() const;
};