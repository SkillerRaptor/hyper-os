#include <Kernel/Boot/stivale2.h>

#include <sys/types.h>
#include <Kernel/Memory/mm.h>

static struct stivale2_header_tag_smp smp_hdr_tag =
{
    .tag =
    {
        .identifier = STIVALE2_HEADER_TAG_SMP_ID,
        .next = 0
    },
    .flags = 0
};

static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag =
{
    .tag =
    {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uintptr_t)&smp_hdr_tag
    },
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};

static uint8_t stack[4096] = { 0 };

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr =
{
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .tags = (uintptr_t)&framebuffer_hdr_tag
};

void* stivale2_get_tag(struct stivale2_struct* stivale2_struct, uint64_t id)
{
    struct stivale2_tag* current_tag = (struct stivale2_tag*)((void*)(stivale2_struct->tags + KERNEL_BASE_ADDRESS));
    while (1)
    {
        if (current_tag == NULL)
            return NULL;

        if (current_tag->identifier == id)
            return current_tag;

        current_tag = (struct stivale2_tag*)((void*)(current_tag->next + KERNEL_BASE_ADDRESS));
    }
}