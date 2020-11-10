#pragma once

#include <LibC/stdint.h>

class IO
{
public:
    static void Out8(uint16_t port, uint8_t value);
    static void Out16(uint16_t port, uint16_t value);
    static void Out32(uint16_t port, uint32_t value);

    static uint8_t In8(uint16_t port);
    static uint16_t In16(uint16_t port);
    static uint32_t In32(uint16_t port);

    static void IoWait();
};