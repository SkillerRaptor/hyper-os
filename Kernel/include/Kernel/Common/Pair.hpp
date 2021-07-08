/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Utilities.hpp>

namespace Kernel
{
	template <typename T1, typename T2>
	class Pair
	{
	public:
		Pair()
			: first()
			, second()
		{
		}

		Pair(const T1& first, const T2& second)
			: first(first)
			, second(second)
		{
		}

		template <class U1 = T1, class U2 = T2>
		Pair(const U1& first, const U2& second)
			: first(first)
			, second(second)
		{
		}

		template <class U1, class U2>
		Pair(const Pair<U1, U2>& other)
			: first(other.first)
			, second(other.second)
		{
		}

		template <class U1, class U2>
		Pair(Pair<U1, U2>&& other)
			: first(move(other.first))
			, second(move(other.second))
		{
		}

		Pair(const Pair& other) = default;
		Pair(Pair&& other) noexcept = default;

		Pair& operator=(const Pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}

		Pair& operator=(Pair&& other) noexcept
		{
			first = Utilities::move(other.first);
			second = Utilities::move(other.second);
			return *this;
		}

	public:
		T1 first{};
		T2 second{};
	};

	template <typename T1, typename T2>
	Pair<T1, T2> make_pair(T1&& first, T2&& second)
	{
		return Pair<T1, T2>(forward<T1>(first), forward<T2>(second));
	}
} // namespace Kernel
