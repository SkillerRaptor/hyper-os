/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Graphics/Color.hpp>
#include <Kernel/Graphics/Rect.hpp>
#include <stivale2.h>

namespace Kernel
{
	class Painter
	{
	public:
		static constexpr const Color s_desktop_color = { 25, 25, 25 };

	private:
		struct FramebufferData
		{
			uint8_t* address;
			uint16_t width;
			uint16_t height;
			uint16_t pitch;
			uint16_t bpp;
		};

	public:
		static void initialize(stivale2_struct_tag_framebuffer* framebuffer_tag);
		static void cleanup();

		static void clear(const Color& color);
		static void draw_rect(const Rect& rect, const Color& color);

		static void swap_buffers();

	private:
		static FramebufferData s_framebuffer_data;
		static uint8_t* s_backbuffer;
	};
} // namespace Kernel
