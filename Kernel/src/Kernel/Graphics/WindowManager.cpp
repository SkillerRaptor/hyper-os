/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Graphics/Painter.hpp>
#include <Kernel/Graphics/WindowManager.hpp>

namespace Kernel
{
	Vector<Window> WindowManager::s_windows = {};

	void WindowManager::add_window(const Window& window)
	{
		s_windows.push_back(window);
	}

	void WindowManager::draw_window(const Window& window)
	{
		Painter::draw_rect(window.rect(), { 100, 100, 100 });
	}

	void WindowManager::draw_windows()
	{
		for (size_t i = 0; i < s_windows.size(); ++i)
		{
			const Window& window = s_windows[i];
			WindowManager::draw_window(window);
		}
	}
} // namespace Kernel
