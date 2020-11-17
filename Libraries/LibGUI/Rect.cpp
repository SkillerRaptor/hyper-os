#include "Rect.h"

Rect::Rect()
	: m_Location(0, 0), m_Width(0), m_Height(0)
{
}

Rect::Rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	: m_Location(x, y), m_Width(width), m_Height(height)
{
}

void Rect::Inflate(uint32_t width, uint32_t height)
{
	SetX(GetX() - width / 2);
	SetWidth(GetWidth() + width);
	SetY(GetY() - height / 2);
	SetHeight(GetHeight() + height);
}

uint32_t Rect::GetLeft() const
{
	return GetX();
}

uint32_t Rect::GetRight() const
{
	return GetX() + GetWidth();
}

uint32_t Rect::GetTop() const
{
	return GetY();
}

uint32_t Rect::GetBottom() const
{
	return GetY() + GetHeight();
}

void Rect::SetX(uint32_t x)
{
	m_Location.SetX(x);
}

uint32_t Rect::GetX() const
{
	return m_Location.GetX();
}

void Rect::SetY(uint32_t y)
{
	m_Location.SetY(y);
}

uint32_t Rect::GetY() const
{
	return m_Location.GetY();
}

void Rect::SetWidth(uint32_t width)
{
	m_Width = width;
}

uint32_t Rect::GetWidth() const
{
	return m_Width;
}

void Rect::SetHeight(uint32_t height)
{
	m_Height = height;
}

uint32_t Rect::GetHeight() const
{
	return m_Height;
}

Point Rect::GetLocation() const
{
	return m_Location;
}

Point Rect::GetCenter() const
{
	return { GetX() + GetWidth() / 2, GetY() + GetHeight() / 2 };
}

bool Rect::Contains(uint32_t x, uint32_t y) const
{
	return x >= m_Location.GetX() && x <= GetRight() && y >= m_Location.GetY() && y <= GetBottom();
}

bool Rect::Contains(const Point& point) const
{
	return Contains(point.GetX(), point.GetY());
}

void Rect::Move(uint32_t x, uint32_t y)
{
	m_Location.Move(x, y);
}

bool Rect::operator==(const Rect& other)
{
	return m_Location == other.m_Location && m_Width == other.m_Width && m_Height == other.m_Height;
}