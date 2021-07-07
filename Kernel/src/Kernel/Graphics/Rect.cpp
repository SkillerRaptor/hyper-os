/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Graphics/Rect.hpp>

namespace Kernel
{
	Rect::Rect(uint32_t x, uint32_t y, size_t width, size_t height)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
	{
	}
	
	void Rect::set_x(uint32_t x)
	{
		m_x = x;
	}
	
	uint32_t Rect::x() const
	{
		return m_x;
	}
	
	void Rect::set_y(uint32_t y)
	{
		m_y = y;
	}
	
	uint32_t Rect::y() const
	{
		return m_y;
	}
	
	void Rect::set_width(size_t width)
	{
		m_width = width;
	}
	
	size_t Rect::width() const
	{
		return m_width;
	}
	
	void Rect::set_height(size_t height)
	{
		m_height = height;
	}
	
	size_t Rect::height() const
	{
		return m_height;
	}
}
