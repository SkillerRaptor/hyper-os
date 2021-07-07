/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/String.hpp>
#include <Kernel/Graphics/Rect.hpp>

namespace Kernel
{
	class Window
	{
	public:
		Window() = default;
		Window(const String& title, const Rect& rect);

		const String& title() const;
		const Rect& rect() const;
		
	private:
		String m_title{};
		Rect m_rect{};
	};
}
