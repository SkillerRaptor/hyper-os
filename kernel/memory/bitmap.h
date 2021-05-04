#ifndef HYPEROS_KERNEL_MEMORY_BITMAP_H_
#define HYPEROS_KERNEL_MEMORY_BITMAP_H_

#include <stddef.h>
#include <stdint.h>

struct bitmap
{
	uint8_t* data;
	size_t size;
};

void bitmap_set_bit(struct bitmap bitmap, size_t index, uint8_t value);
uint8_t bitmap_is_bit(struct bitmap bitmap, size_t index);

#endif // HYPEROS_KERNEL_MEMORY_BITMAP_H_
