/*
 * Copyright (c) 2021, 2020-SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Memory.hpp>
#include <Kernel/Memory/Bitmap.hpp>

namespace Kernel
{
	Bitmap::Bitmap(size_t size) noexcept
		: m_size(size)
	{
	}

	Bitmap::Bitmap(uint8_t* data, size_t size) noexcept
		: m_data(data)
		, m_size(size)
	{
	}

	void Bitmap::set() noexcept
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = 0xFF;
		}
	}

	void Bitmap::set(size_t position, bool value)
	{
		if (position > m_size)
		{
			return;
		}

		uint64_t byte_index;
		uint8_t bit_value;
		get_index(position, byte_index, bit_value);

		if (value)
		{
			m_data[byte_index] |= bit_value;
			return;
		}

		m_data[byte_index] &= ~bit_value;
	}

	void Bitmap::reset() noexcept
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = 0x00;
		}
	}

	void Bitmap::reset(size_t position)
	{
		if (position > m_size)
		{
			return;
		}

		uint64_t byte_index;
		uint8_t bit_value;
		get_index(position, byte_index, bit_value);

		m_data[byte_index] &= ~bit_value;
	}

	void Bitmap::flip() noexcept
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = ~m_data[i];
		}
	}

	void Bitmap::flip(size_t position)
	{
		if (position > m_size)
		{
			return;
		}

		uint64_t byte_index;
		uint8_t bit_value;
		get_index(position, byte_index, bit_value);

		m_data[byte_index] ^= bit_value;
	}

	bool Bitmap::test(size_t position) const noexcept
	{
		if (position > m_size)
		{
			return false;
		}

		uint64_t byte_index;
		uint8_t bit_value;
		get_index(position, byte_index, bit_value);

		return (m_data[byte_index] & bit_value) != 0;
	}

	bool Bitmap::operator[](size_t position) const noexcept
	{
		return test(position);
	}

	void Bitmap::get_index(size_t position, uint64_t& byte_index, uint8_t& bit_value)
	{
		byte_index = position / Memory::s_byte_size;
		bit_value = static_cast<uint8_t>(1 << (position % Memory::s_byte_size));
	}

	void Bitmap::set_data(uint8_t* data) noexcept
	{
		m_data = data;
	}

	uint8_t* Bitmap::data() noexcept
	{
		return m_data;
	}

	const uint8_t* Bitmap::data() const noexcept
	{
		return m_data;
	}

	void Bitmap::set_size(size_t size) noexcept
	{
		m_size = size;
	}

	size_t Bitmap::size() const noexcept
	{
		return m_size;
	}

	size_t Bitmap::max_size() const noexcept
	{
		return m_size;
	}
} // namespace Kernel
