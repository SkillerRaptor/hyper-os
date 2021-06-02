#pragma once

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
		
		constexpr const char* begin() const
		{
			return m_string;
		}
		
		constexpr const char* end() const
		{
			return m_string + m_size;
		}
		
		constexpr const char* data() const
		{
			return m_string;
		}
		
		constexpr size_t size() const
		{
			return m_size;
		}
		
		constexpr bool empty() const
		{
			return m_size == 0;
		}
		
		constexpr const char& at(size_t index) const
		{
			return m_string[index];
		}
		
		const char& operator[](size_t index) const
		{
			return m_string[index];
		}
	
	private:
		const char* m_string{ nullptr };
		size_t m_size{ 0 };
	};
}
