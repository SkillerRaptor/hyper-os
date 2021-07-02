/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/System/CPU.hpp>

namespace Kernel
{
	void CPU::initialize()
	{
		while (true)
		{
			__asm__ __volatile__("hlt");
		}
	}
}
