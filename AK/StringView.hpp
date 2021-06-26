#pragma once

#include <AK/Iterator.hpp>
#include <stddef.h>

namespace AK
{
	class StringView
	{
	public:
		using ValueType = char;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
		using Iterator = SimpleIterator<StringView, ValueType>;
		using ConstIterator = SimpleIterator<const StringView, const ValueType>;
	
	public:
		constexpr StringView() = default;
		
		constexpr StringView(const StringView& other) noexcept
			: m_string(other.data())
			, m_size(other.size())
		{
		}
		
		constexpr StringView(const StringView& string, size_t length)
			: m_string{ string.data() }
			, m_size{ length }
		{
		}
		
		constexpr StringView(const char* string, size_t count)
			: m_string{ string }
			, m_size{ count }
		{
		}
		
		constexpr StringView(const char* string)
			: m_string{ string }
			, m_size{ 0 } // TODO: constexpr strlen
		{
		}
		
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
		
		constexpr const char& at(size_t position) const
		{
			return m_string[position];
		}
		
		const char& operator[](size_t position) const
		{
			return m_string[position];
		}
		
		constexpr const char* data() const
		{
			return m_string;
		}
		
		constexpr size_t length() const
		{
			return m_size;
		}
		
		constexpr size_t size() const
		{
			return m_size;
		}
		
		constexpr size_t max_size() const
		{
			return m_size;
		}
		
		constexpr bool empty() const
		{
			return m_size == 0;
		}
	
	private:
		const char* m_string{ nullptr };
		size_t m_size{ 0 };
	};
}
