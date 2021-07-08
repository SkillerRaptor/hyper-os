/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Vector.hpp>
#include <Kernel/Graphics/Window.hpp>

namespace Kernel
{
	class WindowManager
	{
	public:
		static void add_window(const Window& window);

		static void draw_window(const Window& window);
		static void draw_windows();

	private:
		static Vector<Window> s_windows;
	};
} // namespace Kernel
