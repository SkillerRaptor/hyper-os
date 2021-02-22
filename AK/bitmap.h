#ifndef HYPEROS_AK_BITMAP_H_
#define HYPEROS_AK_BITMAP_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t* data;
    size_t size;
} __PACKED bitmap_t;

void bitmap_set_bit(bitmap_t* bitmap, size_t index, bool value);
bool bitmap_get_bit(bitmap_t bitmap, size_t index);

#endif