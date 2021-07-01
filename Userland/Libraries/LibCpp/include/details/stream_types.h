/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cuchar>

namespace std
{
	using streamoff = long long;
	using streamsize = ptrdiff_t;
	
	template <typename State>
	class fpos
	{
	public:
		// TODO: Implement fpos
	};
	
	using streampos = fpos<mbstate_t>;
	using wstreampos = fpos<mbstate_t>;
	using u8streampos = fpos<mbstate_t>;
	using u16streampos = fpos<mbstate_t>;
	using u32streampos = fpos<mbstate_t>;
}
