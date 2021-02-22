#include <AK/serial.h>

#include <AK/io.h>

#define SERIAL_PORT 0x3F8

int serial_init(void)
{
    io_outb(SERIAL_PORT + 1, 0x00);
    io_outb(SERIAL_PORT + 3, 0x80);
    io_outb(SERIAL_PORT + 0, 0x03);
    io_outb(SERIAL_PORT + 1, 0x00);
    io_outb(SERIAL_PORT + 3, 0x03);
    io_outb(SERIAL_PORT + 2, 0xC7);
    io_outb(SERIAL_PORT + 4, 0x0B);
    io_outb(SERIAL_PORT + 4, 0x1E);
    io_outb(SERIAL_PORT + 0, 0xAE);

    if (io_inb(SERIAL_PORT + 0) != 0xAE)
        return 1;

    io_outb(SERIAL_PORT + 4, 0x0F);
    return 0;
}

int serial_received(void)
{
    return io_inb(SERIAL_PORT + 1) & 1;
}

char serial_read(void)
{
    while (serial_received() == 0);

    return io_inb(SERIAL_PORT);
}

int serial_transmit_empty(void)
{
    return io_inb(SERIAL_PORT + 5) & 0x20;
}

void serial_write(char c)
{
    while (serial_transmit_empty() == 0);

    io_outb(SERIAL_PORT, c);
}

void serial_write_string(const char* str)
{
    while (*str)
        io_outb(SERIAL_PORT, *str++);
}