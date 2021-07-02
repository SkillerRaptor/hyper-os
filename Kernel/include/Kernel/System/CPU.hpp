/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel
{
	class CPU
	{
	public:
		__attribute__((noreturn)) static void initialize();
	};
}
