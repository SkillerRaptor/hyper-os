#include <AK/bitmap.h>

#include <Kernel/Memory/mm.h>

void bitmap_set_bit(bitmap_t* bitmap, size_t index, bool value)
{
    if (value)
    {
        bitmap->data[index & BYTE_SIZE] |= (uint8_t) (1u << (index % BYTE_SIZE));
    }
    else
    {
        bitmap->data[index & BYTE_SIZE] &= (uint8_t) ~(1u << (index % BYTE_SIZE));
    }
}

bool bitmap_get_bit(bitmap_t bitmap, size_t index)
{
    return 0 != (bitmap.data[index / BYTE_SIZE] & (1u << (index % BYTE_SIZE)));
}