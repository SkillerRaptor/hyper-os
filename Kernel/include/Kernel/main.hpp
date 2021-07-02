/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stivale2.h>

namespace Kernel
{
	extern "C" __attribute__((noreturn)) void main(stivale2_struct* bootloader_data);
}
