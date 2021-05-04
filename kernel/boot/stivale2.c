#include "stivale2.h"

#include <mm/memory.h>

#include <stddef.h>

static uint8_t stack[4096] = { 0 };

static struct stivale2_header_tag_smp header_tag_smp =
{
	.tag =
	{
		.identifier = STIVALE2_HEADER_TAG_SMP_ID,
		.next = 0
	},
	.flags = 0
};

static struct stivale2_header_tag_framebuffer header_tag_framebuffer =
{
	.tag =
	{
		.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
		.next = (uintptr_t) &header_tag_smp
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
	.tags = (uintptr_t) &header_tag_framebuffer
};

void* stivale2_get_tag(struct stivale2_struct* stivale2_struct, uint64_t id)
{
	struct stivale2_tag* current_tag = (void*) stivale2_struct->tags + PHYSICAL_MEMORY_OFFSET;
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
