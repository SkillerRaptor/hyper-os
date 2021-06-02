#pragma once

#include <AK/Assertion.hpp>
#include <AK/Iterator.hpp>
#include <stddef.h>

namespace AK
{
	template <typename T, size_t N>
	class Array
	{
	public:
		using ValueType = T;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
		using Iterator = SimpleIterator<Array, ValueType>;
		using ConstIterator = SimpleIterator<const Array, const ValueType>;
	
	public:
		constexpr Array() = default;
		~Array() = default;
		
		constexpr Iterator begin() noexcept
		{
			return Iterator::begin(*this);
		}
		
		constexpr ConstIterator begin() const noexcept
		{
			return ConstIterator::begin(*this);
		}
		
		constexpr ConstIterator cbegin() const noexcept
		{
			return ConstIterator::begin(*this);
		}
		
		constexpr Iterator end() noexcept
		{
			return Iterator::end(*this);
		}
		
		constexpr ConstIterator end() const noexcept
		{
			return ConstIterator::end(*this);
		}
		
		constexpr ConstIterator cend() const noexcept
		{
			return ConstIterator::end(*this);
		}
		
		constexpr Reference at(size_t position)
		{
			VERIFY(position < N);
			return m_data[position];
		}
		
		constexpr ConstReference at(size_t position) const
		{
			VERIFY(position < N);
			return m_data[position];
		}
		
		constexpr Reference operator[](size_t position)
		{
			return m_data[position];
		}
		
		constexpr ConstReference operator[](size_t position) const
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
		
		constexpr bool empty() const noexcept
		{
			return N == 0;
		}
		
		constexpr SizeType size() const noexcept
		{
			return N;
		}
		
		constexpr SizeType max_size() const noexcept
		{
			return N;
		}
		
	private:
		ValueType m_data[N]{ 0 };
	};
}
