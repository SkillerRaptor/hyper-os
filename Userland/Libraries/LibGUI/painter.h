#ifndef HYPEROS_USERLAND_LIBRARIES_LIBGUI_PAINTER_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBGUI_PAINTER_H_

#include <Kernel/Boot/stivale2.h>
#include <LibGUI/color.h>

void painter_init(struct stivale2_struct_tag_framebuffer* framebuffer_tag);

void painter_clear(color_t color);

#endif