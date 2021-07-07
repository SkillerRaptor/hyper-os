/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Graphics/Window.hpp>

namespace Kernel
{
	Window::Window(const String& title, const Rect& rect)
		: m_title(title)
		, m_rect(rect)
	{
	}
	
	const String& Window::title() const
	{
		return m_title;
	}
	
	const Rect& Window::rect() const
	{
		return m_rect;
	}
}
