#ifndef HYPEROS_KERNEL_MEMORY_BITMAP_H_
#define HYPEROS_KERNEL_MEMORY_BITMAP_H_

#include <stdint.h>

void bitmap_set_bit(uint8_t* bitmap, uint64_t index, uint8_t value);
uint8_t bitmap_get_bit(uint8_t* bitmap, uint64_t index);

#endif // HYPEROS_KERNEL_MEMORY_BITMAP_H_
