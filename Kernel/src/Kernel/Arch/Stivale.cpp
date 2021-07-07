/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Arch/Stivale.hpp>
#include <Kernel/Common/Memory.hpp>

namespace Kernel
{
	static uint8_t s_stack[4096] = { 0 };

	static stivale2_tag s_unmap_null_tag = {
		.identifier = STIVALE2_HEADER_TAG_UNMAP_NULL_ID,
		.next = 0
	};

	static stivale2_header_tag_smp s_smp_header_tag = {
		.tag = {
			.identifier = STIVALE2_HEADER_TAG_SMP_ID,
			.next = reinterpret_cast<uintptr_t>(&s_unmap_null_tag)
		},
		.flags = 0
	};

	static stivale2_header_tag_framebuffer s_framebuffer_header_tag = {
		.tag = {
			.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
			.next = reinterpret_cast<uintptr_t>(&s_smp_header_tag)
		},
		.framebuffer_width = 0,
		.framebuffer_height = 0,
		.framebuffer_bpp = 0
	};

	__attribute__((section(".stivale2hdr"), used)) static stivale2_header s_bootloader_header = {
		.entry_point = 0,
		.stack = reinterpret_cast<uintptr_t>(s_stack + sizeof(s_stack)),
		.flags = 0,
		.tags = reinterpret_cast<uintptr_t>(&s_framebuffer_header_tag)
	};

	void* stivale2_get_tag(stivale2_struct* bootloader_data, uint64_t identifier)
	{
		auto* current_tag = reinterpret_cast<stivale2_tag*>(bootloader_data->tags + s_physical_memory_offset);
		while (true)
		{
			if (current_tag == nullptr)
			{
				return nullptr;
			}

			if (current_tag->identifier == identifier)
			{
				return current_tag;
			}

			current_tag = reinterpret_cast<stivale2_tag*>(current_tag->next + s_physical_memory_offset);
		}
	}
} // namespace Kernel
