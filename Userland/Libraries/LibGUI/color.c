#include <LibGUI/color.h>

uint32_t color_get_value(color_t color)
{
    return (color.red << 16) + (color.green << 8) + (color.blue << 0);
}

color_t color_get_rgb(uint32_t value)
{
    color_t color;
    color.red = (value >> 0) & 255;
    color.green = (value >> 8) & 255;
    color.blue = (value >> 16) & 255;
    return color;
}