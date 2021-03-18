#include <LibGUI/painter.h>

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <AK/logger.h>
#include <Kernel/Memory/kmm.h>

struct stivale2_struct_tag_framebuffer* framebuffer;

void painter_init(struct stivale2_struct_tag_framebuffer* framebuffer_tag)
{
    framebuffer = framebuffer_tag;
}

void painter_clear(color_t color)
{
	uint8_t* screen = (uint8_t*)framebuffer->framebuffer_addr;
	for (size_t y = 0; y < framebuffer->framebuffer_height; ++y)
	{
		size_t screen_position_y = y * framebuffer->framebuffer_pitch;
		for (size_t x = 0; x < framebuffer->framebuffer_width; ++x)
		{
			size_t screen_position_x = x * (framebuffer->framebuffer_bpp / 8);
			screen[screen_position_x + screen_position_y + 0] = color.blue;
			screen[screen_position_x + screen_position_y + 1] = color.green;
			screen[screen_position_x + screen_position_y + 2] = color.red;
		}
	}
}