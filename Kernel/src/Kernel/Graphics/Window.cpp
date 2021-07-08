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

	void Window::set_title(const String& title)
	{
		m_title = title;
	}

	const String& Window::title() const
	{
		return m_title;
	}

	void Window::set_rect(const Rect& rect)
	{
		m_rect = rect;
	}

	const Rect& Window::rect() const
	{
		return m_rect;
	}
} // namespace Kernel
