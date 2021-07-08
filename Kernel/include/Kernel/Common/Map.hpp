/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Pair.hpp>
#include <Kernel/Common/Vector.hpp>
#include <stddef.h>

namespace Kernel
{
	template <typename Key, typename T>
	class Map
	{
	public:
		T& operator[](const Key& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Pair<Key, T>& value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}
			
			return m_data.emplace_back(x, T()).second;
		}

		T& operator[](Key&& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Pair<Key, T>& value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}
			
			return m_data.emplace_back(move(x), T()).second;
		}

		T& at(const Key& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Pair<Key, T>& value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}
			
			// TODO: Assert / Panic here
		}

		const T& at(const Key& x) const
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				const Pair<Key, T>& value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}

			// TODO: Assert / Panic here
		}

		void clear() noexcept
		{
			m_data.clear();
		}
		
		[[nodiscard]] size_t size() const noexcept
		{
			return m_data.size();
		}
		
		[[nodiscard]] size_t max_size() const noexcept
		{
			return m_data.max_size();
		}
		
		[[nodiscard]] bool empty() const noexcept
		{
			return size() == 0;
		}
	
	private:
		Vector<Pair<Key, T>> m_data{};
	};
} // namespace Kernel
