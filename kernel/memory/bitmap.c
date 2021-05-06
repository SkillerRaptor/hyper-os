#include "bitmap.h"

#include "memory.h"

void bitmap_set_bit(struct bitmap* bitmap, size_t index, uint8_t value)
{
	if (index > (bitmap->size * BYTE_SIZE))
	{
		return;
	}
	
	size_t byte_index = index / BYTE_SIZE;
	size_t bit_index = index % BYTE_SIZE;
	uint64_t bit_value = (1u << (bit_index));
	
	if (value == 0)
	{
		bitmap->data[byte_index] &= (uint8_t) ~bit_value;
		return;
	}
	
	bitmap->data[byte_index] |= (uint8_t) bit_value;
	return;
}

uint8_t bitmap_get_bit(struct bitmap* bitmap, size_t index)
{
	if (index > (bitmap->size * BYTE_SIZE))
	{
		return 0;
	}
	
	size_t byte_index = index / BYTE_SIZE;
	size_t bit_index = index % BYTE_SIZE;
	uint64_t bit_value = 1u << (bit_index);
	return (bitmap->data[byte_index] & bit_value) != 0;
}
