#ifndef HYPEROS_USERLAND_LIBRARIES_LIBGUI_COLOR_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBGUI_COLOR_H_

#include <stdint.h>

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

uint32_t color_get_value(color_t color);
color_t color_get_rgb(uint32_t value);

#endif