#ifndef HYPEROS_KERNEL_SYSTEM_IO_SERVICE_H_
#define HYPEROS_KERNEL_SYSTEM_IO_SERVICE_H_

#include <stdint.h>

void io_outb(uint16_t port, uint8_t value);
uint8_t io_inb(uint16_t port);

void io_wait(void);

#endif // HYPEROS_KERNEL_SYSTEM_IO_SERVICE_H_
