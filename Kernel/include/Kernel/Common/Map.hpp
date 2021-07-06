/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <Kernel/Common/Pair.hpp>
#include <Kernel/Common/Vector.hpp>

namespace Kernel
{
	template <typename Key, typename T>
	class Map
	{
	public:
		using KeyType = Key;
		using MappedType = T;
		using ValueType = Pair<KeyType, MappedType>;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;

	public:
		[[nodiscard]] bool empty() const noexcept
		{
			return size() == 0;
		}

		SizeType size() const noexcept
		{
			return m_data.size();
		}

		SizeType max_size() const noexcept
		{
			return m_data.max_size();
		}

		MappedType& operator[](const KeyType& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Reference value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}
			
			return m_data.emplace_back(x, MappedType()).second;
		}

		MappedType& operator[](KeyType&& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Reference value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}
			
			return m_data.emplace_back(move(x), MappedType()).second;
		}

		MappedType& at(const KeyType& x)
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				Reference value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}

			// Assert
		}

		const MappedType& at(const KeyType& x) const
		{
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				ConstReference value = m_data[i];
				if (value.first == x)
				{
					return value.second;
				}
			}

			// Assert
		}

		void clear() noexcept
		{
			m_data.clear();
		}

	private:
		Vector<ValueType> m_data{};
	};
} // namespace Kernel
