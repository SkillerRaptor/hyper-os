/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel::Utilities
{
	template <typename T>
	struct RemoveReference
	{
		using Type = T;
	};
	
	template <typename T>
	struct RemoveReference<T&>
	{
		using Type = T;
	};
	
	template <typename T>
	struct RemoveReference<T&&>
	{
		using Type = T;
	};
	
	template <typename T>
	constexpr T&& forward(typename RemoveReference<T>::Type& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template <typename T>
	constexpr T&& forward(typename RemoveReference<T>::Type&& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template <typename T>
	constexpr typename RemoveReference<T>::Type&& move(T&& t) noexcept
	{
		return static_cast<typename RemoveReference<T>::Type&&>(t);
	}
}
