#pragma once

#include <AK/Assertion.hpp>
#include <AK/Iterator.hpp>

namespace AK
{
	template <typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
		using Iterator = SimpleIterator<Vector, ValueType>;
		using ConstIterator = SimpleIterator<const Vector, const ValueType>;
	
	public:
		Iterator begin() noexcept
		{
			return Iterator::begin(*this);
		}
		
		ConstIterator begin() const noexcept
		{
			return ConstIterator::begin(*this);
		}
		
		ConstIterator cbegin() const noexcept
		{
			return ConstIterator::begin(*this);
		}
		
		Iterator end() noexcept
		{
			return Iterator::end(*this);
		}
		
		ConstIterator end() const noexcept
		{
			return ConstIterator::end(*this);
		}
		
		ConstIterator cend() const noexcept
		{
			return ConstIterator::end(*this);
		}
		
		Reference at(size_t position)
		{
			VERIFY(position < N);
			return m_data[position];
		}
		
		ConstReference at(size_t position) const
		{
			VERIFY(position < N);
			return m_data[position];
		}
		
		Reference operator[](size_t position)
		{
			return m_data[position];
		}
		
		ConstReference operator[](size_t position) const
		{
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
		
		bool empty() const noexcept
		{
			return m_size == 0;
		}
		
		SizeType size() const noexcept
		{
			return m_size;
		}
		
		SizeType max_size() const noexcept
		{
			return m_size;
		}
	
	private:
		Pointer m_data{ nullptr };
		SizeType m_size{ 0 };
		SizeType m_capacity{ 0 };
	};
}
