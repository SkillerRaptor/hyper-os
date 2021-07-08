/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Utilities.hpp>
#include <Kernel/Memory/KernelMemory.hpp>
#include <stddef.h>

namespace Kernel
{
	template <typename T>
	class Vector
	{
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

		template <typename... Args>
		T& emplace_back(Args&&... args)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size] = T(Utilities::forward<Args>(args)...);
			return m_data[m_size++];
		}

		void push_back(const T& value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = value;
		}

		void push_back(T&& value)
		{
			if (m_size >= m_capacity)
			{
				grow(m_capacity + m_capacity / 2);
			}

			m_data[m_size++] = Utilities::move(value);
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
			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i].~T();
			}

			m_size = 0;
		}

		T& operator[](size_t position)
		{
			return m_data[position];
		}

		const T& operator[](size_t position) const
		{
			return m_data[position];
		}

		T& at(size_t position)
		{
			// TODO: Assert / Panic here
			return m_data[position];
		}

		const T& at(size_t position) const
		{
			// TODO: Assert / Panic here
			return m_data[position];
		}

		T* data() noexcept
		{
			return m_data;
		}

		const T* data() const noexcept
		{
			return m_data;
		}

		[[nodiscard]] size_t size() const noexcept
		{
			return m_size;
		}

		[[nodiscard]] size_t max_size() const noexcept
		{
			return m_capacity;
		}

		[[nodiscard]] bool empty() const noexcept
		{
			return size() == 0;
		}

	private:
		void grow(size_t capacity)
		{
			auto* data_block = new T[capacity];

			if (capacity < m_size)
			{
				m_size = capacity;
			}

			for (size_t i = 0; i < m_size; ++i)
			{
				data_block[i] = Utilities::move(m_data[i]);
			}

			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i].~T();
			}

			delete[] m_data;
			m_data = data_block;
			m_capacity = capacity;
		}

	private:
		T* m_data{ nullptr };
		size_t m_size{ 0 };
		size_t m_capacity{ 0 };
	};
} // namespace Kernel
