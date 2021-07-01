/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstring>
#include <cuchar>
#include <ios>
#include <type_traits>

namespace std
{
	template <typename T>
	struct _char_types
	{
		using int_type = unsigned long;
		using pos_type = streampos;
		using off_type = streamoff;
		using state_type = mbstate_t;
	};

	template <typename T>
	class char_traits
	{
	public:
		using char_type = T;
		using int_type = typename _char_types<T>::int_type;
		using pos_type = typename _char_types<T>::pos_type;
		using off_type = typename _char_types<T>::off_type;
		using state_type = typename _char_types<T>::state_type;

	public:
		static constexpr size_t length(const char_type* string)
		{
			if (string == nullptr)
			{
				return 0;
			}

			if (is_constant_evaluated())
			{
				size_t length = 0;
				
				while (*(string++))
				{
					++length;
				}
				
				return length;
			}

			return std::strlen(__s);
		}

		// TODO: Implement char_traits
	};
} // namespace std
