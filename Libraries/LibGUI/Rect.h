#pragma once

#include <LibGUI/Point.h>

class Rect
{
private:
	Point m_Location;
	uint32_t m_Width;
	uint32_t m_Height;

public:
	Rect();
	Rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	void Inflate(uint32_t width, uint32_t height);

	uint32_t GetLeft() const;
	uint32_t GetRight() const;
	uint32_t GetTop() const;
	uint32_t GetBottom() const;

	void SetX(uint32_t x);
	uint32_t GetX() const;

	void SetY(uint32_t y);
	uint32_t GetY() const;

	void SetWidth(uint32_t width);
	uint32_t GetWidth() const;

	void SetHeight(uint32_t height);
	uint32_t GetHeight() const;

	Point GetLocation() const;
	Point GetCenter() const;

	bool Contains(uint32_t x, uint32_t y) const;
	bool Contains(const Point& point) const;

	void Move(uint32_t x, uint32_t y);

	bool operator==(const Rect& other);
};