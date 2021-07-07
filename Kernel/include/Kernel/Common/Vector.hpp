/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Utility.hpp>
#include <Kernel/Memory/KernelMemory.hpp>
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
			clear();
			delete[] m_data;
		}

		[[nodiscard]] bool empty() const noexcept
		{
			return size() == 0;
		}

		SizeType size() const noexcept
		{
			return m_size;
		}

		SizeType max_size() const noexcept
		{
			return m_capacity;
		}

		Reference operator[](SizeType position)
		{
			return m_data[position];
		}

		ConstReference operator[](SizeType position) const
		{
			return m_data[position];
		}

		Reference at(SizeType position)
		{
			// Assert
			return m_data[position];
		}

		ConstReference at(SizeType position) const
		{
			// Assert
			return m_data[position];
		}

		Pointer data() noexcept
		{
			return m_data;
		}

		ConstPointer data() const noexcept
		{
			return m_data;
		}

		template <typename... Args>
		T& emplace_back(Args&&... args)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size] = T(forward<Args>(args)...);
			return m_data[m_size++];
		}

		void push_back(ConstReference value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = value;
		}

		void push_back(ValueType&& value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = move(value);
		}

		void pop_back()
		{
			if (m_size > 0)
			{
				--m_size;
				m_data[m_size].~T();
			}
		}

		void clear() noexcept
		{
			for (SizeType i = 0; i < m_size; ++i)
			{
				m_data[i].~ValueType();
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
				data_block[i] = move(m_data[i]);
			}
			
			for (SizeType i = 0; i < m_size; ++i)
			{
				m_data[i].~ValueType();
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
