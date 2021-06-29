/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace AK::Math
{
	static constexpr uint64_t div_round_up(uint64_t a, uint64_t b)
	{
		return (a + (b - 1)) / b;
	}
	
	static constexpr uint64_t align_up(uint64_t a, uint64_t b)
	{
		return div_round_up(a, b) * b;
	}
	
	static constexpr uint64_t align_down(uint64_t a, uint64_t b)
	{
		return (a / b) * b;
	}
}
