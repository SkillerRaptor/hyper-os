/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stivale2.h>

namespace Kernel
{
	void* stivale2_get_tag(stivale2_struct* bootloader_data, uint64_t identifier);
}
