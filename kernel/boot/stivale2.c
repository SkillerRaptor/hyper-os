#include "stivale2.h"

#include <memory/memory.h>

#include <stddef.h>

static uint8_t stack[4096] = { 0 };

static struct stivale2_header_tag_smp smp_tag =
{
	.tag =
	{
		.identifier = STIVALE2_HEADER_TAG_SMP_ID,
		.next = 0
	},
	.flags = 0
};

static struct stivale2_header_tag_framebuffer framebuffer_tag =
{
	.tag =
	{
		.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
		.next = (uintptr_t) &smp_tag
	},
	.framebuffer_width = 0,
	.framebuffer_height = 0,
	.framebuffer_bpp = 0
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header header =
{
	.entry_point = 0,
	.stack = (uintptr_t) stack + sizeof(stack),
	.flags = 0,
	.tags = (uintptr_t) &framebuffer_tag
};

void* stivale2_get_tag(struct stivale2_struct* bootloader_data, uint64_t id)
{
	struct stivale2_tag* current_tag = (void*) bootloader_data->tags + PHYSICAL_MEMORY_OFFSET;
	for (;;)
	{
		if (current_tag == NULL)
		{
			return NULL;
		}
		
		if (current_tag->identifier == id)
		{
			return current_tag;
		}
		
		current_tag = (void*) current_tag->next + PHYSICAL_MEMORY_OFFSET;
	}
}
