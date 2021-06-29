/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace AK
{
	static constexpr const uint8_t s_byte_size{ 8 };
	static constexpr const uint16_t s_page_size{ 4096 };
	static constexpr const uint64_t s_physical_memory_offset{ 0xFFFF800000000000 };
	static constexpr const uint64_t s_kernel_base_address{ 0xFFFFFFFF80000000 };
}
