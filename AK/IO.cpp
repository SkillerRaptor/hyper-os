#include "IO.h"

void IO::Out8(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1"
        :: "a"(value), "Nd"(port));
}

void IO::Out16(uint16_t port, uint16_t value)
{
    asm volatile("outw %0, %1"
        :: "a"(value), "Nd"(port));
}

void IO::Out32(uint16_t port, uint32_t value)
{
    asm volatile("outl %0, %1"
        :: "a"(value), "Nd"(port));
}

uint8_t IO::In8(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
        : "=a"(ret)
        : "Nd"(port));
    return ret;
}

uint16_t IO::In16(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
        : "=a"(ret)
        : "Nd"(port));
    return ret;
}

uint32_t IO::In32(uint16_t port)
{
    uint32_t ret;
    asm volatile("inl %1, %0"
        : "=a"(ret)
        : "Nd"(port));
    return ret;
}

void IO::IoWait()
{
    Out8(0x80, 0);
}