/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

namespace AK
{
	class Bitmap
	{
	public:
		using ValueType = uint8_t;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
	public:
		constexpr Bitmap() noexcept = default;
		
		explicit Bitmap(SizeType size) noexcept;
		Bitmap(Pointer data, SizeType size) noexcept;
		
		Bitmap& set() noexcept;
		Bitmap& set(SizeType position, bool value = true);
		
		Bitmap& reset() noexcept;
		Bitmap& reset(SizeType position);
		
		Bitmap& flip() noexcept;
		Bitmap& flip(SizeType position);
		
		bool test(SizeType position) const noexcept;
		bool operator[](SizeType position) const noexcept;
		
		void set_data(Pointer data) noexcept;
		Pointer data() noexcept;
		ConstPointer data() const noexcept;
		
		void set_size(SizeType size) noexcept;
		SizeType size() const noexcept;
		SizeType max_size() const noexcept;
	
	private:
		Pointer m_data{ nullptr };
		SizeType m_size{ 0 };
	};
}
