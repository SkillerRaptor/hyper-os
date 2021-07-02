/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Utility.hpp>
#include <stddef.h>

namespace Kernel
{
	template <typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Reference = T&;
		using ConstReference = const T&;
		using Pointer = T*;
		using ConstPointer = const T*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;

	public:
		Vector()
		{
			grow(2);
		}

		~Vector()
		{
			delete[] m_data;
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return size() == 0;
		}

		constexpr SizeType size() const noexcept
		{
			return m_size;
		}

		constexpr SizeType max_size() const noexcept
		{
			return m_capacity;
		}

		constexpr Reference operator[](SizeType position)
		{
			return m_data[position];
		}

		constexpr ConstReference operator[](SizeType position) const
		{
			return m_data[position];
		}

		constexpr Reference at(SizeType position)
		{
			return m_data[position];
		}

		constexpr ConstReference at(SizeType position) const
		{
			return m_data[position];
		}

		constexpr Pointer data() noexcept
		{
			return m_data;
		}

		constexpr ConstPointer data() const noexcept
		{
			return m_data;
		}

		template <typename... Args>
		constexpr T& emplace_back(Args&&... args)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size] = T(forward<Args>(args)...);
			return m_data[m_size++];
		}

		constexpr void push_back(ConstReference value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = value;
		}

		constexpr void push_back(ValueType&& value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = move(value);
		}

		constexpr void pop_back()
		{
			if (m_size > 0)
			{
				--m_size;
				m_data[m_size].~T();
			}
		}

		constexpr void clear() noexcept
		{
			for (SizeType i = 0; i < m_size; ++i)
			{
				m_data[i].~T();
			}
			
			m_size = 0;
		}

	private:
		void grow(SizeType capacity)
		{
			auto* data_block = new ValueType[capacity];

			if (capacity < m_size)
			{
				m_size = capacity;
			}

			for (SizeType i = 0; i < m_size; ++i)
			{
				data_block[i] = m_data[i];
			}

			delete[] m_data;
			m_data = data_block;
			m_capacity = capacity;
		}

	private:
		Pointer m_data{ nullptr };
		SizeType m_size{ 0 };
		SizeType m_capacity{ 0 };
	};
} // namespace Kernel
