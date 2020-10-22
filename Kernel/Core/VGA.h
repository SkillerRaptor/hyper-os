#pragma once

#include <LibC/stdint.h>

enum VGA_COLOR
{
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_BROWN,
	WHITE
};

static inline uint8_t VGA_ENTRY_COLOR(VGA_COLOR foreground, VGA_COLOR background)
{
	return foreground | background << 4;
}

static inline uint16_t VGA_ENTRY(unsigned char c, uint8_t color)
{
	return (uint16_t)c | (uint16_t)color << 8;
}