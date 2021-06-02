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
