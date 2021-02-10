#include <LibGUI/Color.h>

Color::Color()
	: m_Value(0)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
	: m_Value((r << 16) + (g << 8) + b)
{
}

uint32_t Color::GetValue() const
{
	return m_Value;
}
