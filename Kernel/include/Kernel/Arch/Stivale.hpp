/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stivale2.h>

namespace Kernel::Stivale
{
	void* get_tag(stivale2_struct* bootloader_data, uint64_t identifier);
} // namespace Kernel::Stivale
