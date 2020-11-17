#include "Point.h"

Point::Point()
	: m_X(0), m_Y(0)
{
}

Point::Point(uint32_t x, uint32_t y)
	: m_X(x), m_Y(y)
{
}

void Point::SetX(uint32_t x)
{
	m_X = x;
}

uint32_t Point::GetX() const
{
	return m_X;
}

void Point::SetY(uint32_t y)
{
	m_Y = y;
}

uint32_t Point::GetY() const
{
	return m_Y;
}

void Point::Move(uint32_t x, uint32_t y)
{
	m_X += x;
	m_Y += y;
}

bool Point::operator==(const Point& point) const
{
	return m_X == point.m_X && m_Y == point.m_Y;
}
