/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

namespace AK
{
	template <class C, typename T>
	class SimpleIterator
	{
	public:
		using ValueType = T;
		using Reference = ValueType&;
		using Pointer = ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
		using ContainerType = C;
		
		friend ContainerType;
	
	public:
		constexpr const ValueType& operator*() const
		{
			return m_container[m_position];
		}
		
		constexpr ValueType& operator*()
		{
			return m_container[m_position];
		}
		
		constexpr const ValueType* operator->() const
		{
			return &m_container[m_position];
		}
		
		constexpr ValueType* operator->()
		{
			return &m_container[m_position];
		}
		
		constexpr SimpleIterator operator++()
		{
			++m_position;
			return *this;
		}
		
		constexpr SimpleIterator operator++(int)
		{
			++m_position;
			return SimpleIterator{ m_container, m_position - 1 };
		}
		
		constexpr SimpleIterator operator--()
		{
			--m_position;
			return *this;
		}
		
		constexpr SimpleIterator operator--(int)
		{
			--m_position;
			return SimpleIterator{ m_container, m_position + 1 };
		}
		
		constexpr bool operator==(SimpleIterator other) const
		{
			return m_position == other.m_position;
		}
		
		constexpr bool operator!=(SimpleIterator other) const
		{
			return m_position != other.m_position;
		}
		
		constexpr bool operator<(SimpleIterator other) const
		{
			return m_position < other.m_position;
		}
		
		constexpr bool operator>(SimpleIterator other) const
		{
			return m_position > other.m_position;
		}
		
		constexpr bool operator<=(SimpleIterator other) const
		{
			return m_position <= other.m_position;
		}
		
		constexpr bool operator>=(SimpleIterator other) const
		{
			return m_position >= other.m_position;
		}
	
	private:
		constexpr SimpleIterator(ContainerType& container, SizeType position)
			: m_container(container)
			, m_position(position)
		{
		}
		
		static constexpr SimpleIterator begin(ContainerType& container)
		{
			return { container, 0 };
		}
		
		static constexpr SimpleIterator end(ContainerType& container)
		{
			return { container, container.size() };
		}
	
	private:
		ContainerType& m_container;
		SizeType m_position{ 0 };
	};
}
