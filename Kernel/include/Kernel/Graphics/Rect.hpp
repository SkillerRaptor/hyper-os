/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Kernel
{
	class Rect
	{
	public:
		Rect() = default;
		Rect(uint32_t x, uint32_t y, size_t width, size_t height);
		
		void set_x(uint32_t x);
		uint32_t x() const;
		
		void set_y(uint32_t y);
		uint32_t y() const;
		
		void set_width(size_t width);
		size_t width() const;
		
		void set_height(size_t height);
		size_t height() const;
		
	private:
		uint32_t m_x{ 0 };
		uint32_t m_y{ 0 };
		size_t m_width{ 0 };
		size_t m_height{ 0 };
	};
}
