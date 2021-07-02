/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel
{
	template <typename T>
	struct RemoveReference
	{
		using type = T;
	};
	
	template <typename T>
	struct RemoveReference<T&>
	{
		using type = T;
	};
	
	template <typename T>
	struct RemoveReference<T&&>
	{
		using type = T;
	};
	
	template <typename T>
	constexpr T&& forward(typename RemoveReference<T>::type& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template <typename T>
	constexpr T&& forward(typename RemoveReference<T>::type&& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template <typename T>
	constexpr typename RemoveReference<T>::type&& move(T&& t) noexcept
	{
		return static_cast<typename RemoveReference<T>::type&&>(t);
	}
}
