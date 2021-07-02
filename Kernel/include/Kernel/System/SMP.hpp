/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stivale2.h>

namespace Kernel
{
	class SMP
	{
	private:
	
	public:
		static void initialize(stivale2_struct_tag_smp* smp_tag);
	};
}
