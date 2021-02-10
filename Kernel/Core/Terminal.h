#pragma once

#include <stddef.h>
#include <stdint.h>

class Terminal
{
private:
    static size_t VGA_WIDTH;
    static size_t VGA_HEIGHT;
    static uint16_t* VGA_MEMORY;

    static size_t m_Row;
    static size_t m_Column;
    static uint8_t m_Color;
    static uint16_t* m_Buffer;

public:
    static void Initialize();

    static void PutChar(unsigned char c);
    static void Write(const char* string, size_t size);
    static void WriteString(const char* string);

private:
    static void SetColor(uint8_t color);
    static void PutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y);
};