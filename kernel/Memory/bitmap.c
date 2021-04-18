#include "bitmap.h"

#include "memory.h"

void bitmap_set_bit(uint8_t* bitmap, uint64_t index, uint8_t value)
{
	if (value != 0)
	{
		bitmap[index / BYTE_SIZE] |= (uint8_t) (1u << (index % BYTE_SIZE));
	}
	else
	{
		bitmap[index / BYTE_SIZE] &= (uint8_t) ~(1u << (index % BYTE_SIZE));
	}
}

uint8_t bitmap_get_bit(uint8_t* bitmap, uint64_t index)
{
	return 0 != (bitmap[index / BYTE_SIZE] & (1u << (index % BYTE_SIZE)));
}