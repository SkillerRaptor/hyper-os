#include "Terminal.h"

#include <LibC/string.h>

#include "VGA.h"

size_t Terminal::VGA_WIDTH = 80;
size_t Terminal::VGA_HEIGHT = 25;
uint16_t* Terminal::VGA_MEMORY = (uint16_t*)0xB8000;

size_t Terminal::m_Row;
size_t Terminal::m_Column;
uint8_t Terminal::m_Color;
uint16_t* Terminal::m_Buffer;

void Terminal::Initialize()
{
    m_Row = 0;
    m_Column = 0;
    m_Color = VGA_ENTRY_COLOR(LIGHT_GREY, BLACK);
    m_Buffer = (uint16_t*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            m_Buffer[index] = VGA_ENTRY(' ', m_Color);
        }
    }
}

void Terminal::PutChar(unsigned char c)
{
	if (c == '\t')
	{
        for (size_t i = 0; i < 4; i++)
            PutEntryAt(' ', m_Color, m_Column++, m_Row);
		return;
	}

    if (c == '\n')
    {
        m_Row++;
        m_Column = 0;
        return;
    }

    PutEntryAt(c, m_Color, m_Column++, m_Row);

	if (m_Column >= VGA_WIDTH) {
		m_Row++;
        m_Column = 0;
	}

    if (m_Row >= VGA_HEIGHT)
	{
		memmove(m_Buffer, m_Buffer + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1) * sizeof(uint16_t));

        for (size_t x = 0; x < VGA_WIDTH - 1; x++)
            PutEntryAt(' ', m_Color, x + 1, VGA_HEIGHT - 1);

        m_Row = VGA_HEIGHT - 1;
    }
}

void Terminal::Write(const char* string, size_t size)
{
    for (size_t i = 0; i < size; i++)
        PutChar(string[i]);
}

void Terminal::WriteString(const char* string)
{
    Write(string, strlen(string));
}

void Terminal::SetColor(uint8_t color)
{
    m_Color = color;
}

void Terminal::PutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    m_Buffer[index] = VGA_ENTRY(c, color);
}