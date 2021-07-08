/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Kernel
{
	class Bitmap
	{
	public:
		constexpr Bitmap() noexcept = default;
		
		explicit Bitmap(size_t size) noexcept;
		Bitmap(uint8_t* data, size_t size) noexcept;
		
		void set() noexcept;
		void set(size_t position, bool value = true);
		
		void reset() noexcept;
		void reset(size_t position);
		
		void flip() noexcept;
		void flip(size_t position);
		
		[[nodiscard]] bool test(size_t position) const noexcept;
		[[nodiscard]] bool operator[](size_t position) const noexcept;
		
		void set_data(uint8_t* data) noexcept;
		[[nodiscard]] uint8_t* data() noexcept;
		[[nodiscard]] const uint8_t* data() const noexcept;
		
		void set_size(size_t size) noexcept;
		[[nodiscard]] size_t size() const noexcept;
		[[nodiscard]] size_t max_size() const noexcept;

	private:
		static void get_index(size_t position, uint64_t& byte_index, uint8_t& bit_value);
		
	private:
		uint8_t* m_data{ nullptr };
		size_t m_size{ 0 };
	};
}
