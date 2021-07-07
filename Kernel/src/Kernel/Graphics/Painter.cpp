/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Memory.hpp>
#include <Kernel/Graphics/Painter.hpp>
#include <Kernel/Synchronization/Spinlock.hpp>
#include <stddef.h>

namespace Kernel
{
	Painter::FramebufferData Painter::s_framebuffer_data{};
	uint8_t* Painter::s_backbuffer{ nullptr };
	
	void Painter::initialize(stivale2_struct_tag_framebuffer* framebuffer_tag)
	{
		s_framebuffer_data.address = reinterpret_cast<uint8_t*>(framebuffer_tag->framebuffer_addr);
		s_framebuffer_data.width = framebuffer_tag->framebuffer_width;
		s_framebuffer_data.height = framebuffer_tag->framebuffer_height;
		s_framebuffer_data.pitch = framebuffer_tag->framebuffer_pitch;
		s_framebuffer_data.bpp = framebuffer_tag->framebuffer_bpp;
		
		s_backbuffer = new uint8_t[s_framebuffer_data.height * s_framebuffer_data.pitch];
	}
	
	void Painter::cleanup()
	{
		delete[] s_backbuffer;
	}
	
	void Painter::clear(const Color& color)
	{
		for (size_t y = 0; y < s_framebuffer_data.height; ++y)
		{
			const size_t screen_position_y = y * s_framebuffer_data.pitch;
			for (size_t x = 0; x < s_framebuffer_data.width; ++x)
			{
				const size_t screen_position_x = x * (s_framebuffer_data.bpp / 8);
				s_backbuffer[screen_position_x + screen_position_y + 0] = color.b;
				s_backbuffer[screen_position_x + screen_position_y + 1] = color.g;
				s_backbuffer[screen_position_x + screen_position_y + 2] = color.r;
			}
		}
	}
	
	void Painter::draw_rect(const Rect& rect, const Color& color)
	{
		for (size_t y = rect.y(); y < rect.height(); ++y)
		{
			const size_t screen_position_y = y * s_framebuffer_data.pitch;
			for (size_t x = rect.x(); x < rect.width(); ++x)
			{
				const size_t screen_position_x = x * (s_framebuffer_data.bpp / 8);
				s_backbuffer[screen_position_x + screen_position_y + 0] = color.b;
				s_backbuffer[screen_position_x + screen_position_y + 1] = color.g;
				s_backbuffer[screen_position_x + screen_position_y + 2] = color.r;
			}
		}
	}
	
	void Painter::swap_buffers()
	{
		memcpy(s_framebuffer_data.address, s_backbuffer, s_framebuffer_data.height * s_framebuffer_data.pitch);
	}
}
