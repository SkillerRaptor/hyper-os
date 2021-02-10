#pragma once

#include <stdint.h>

class Point
{
private:
	uint32_t m_X;
	uint32_t m_Y;

public:
	Point();
	Point(uint32_t x, uint32_t y);

	void SetX(uint32_t x);
	uint32_t GetX() const;

	void SetY(uint32_t y);
	uint32_t GetY() const;

	void Move(uint32_t x, uint32_t y);

	bool operator==(const Point& point) const;
};