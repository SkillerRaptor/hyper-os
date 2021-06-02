#pragma once

#include <AK/Iterator.hpp>
#include <stddef.h>

namespace AK
{
	class String
	{
	public:
		using ValueType = char;
		using Reference = ValueType&;
		using ConstReference = const ValueType&;
		using Pointer = ValueType*;
		using ConstPointer = const ValueType*;
		using SizeType = size_t;
		using DifferenceType = ptrdiff_t;
		
		using Iterator = SimpleIterator<String, ValueType>;
		using ConstIterator = SimpleIterator<const String, const ValueType>;
	
	public:
		String() = default;
		
		Iterator begin() noexcept;
		ConstIterator begin() const noexcept;
		ConstIterator cbegin() const noexcept;
		Iterator end() noexcept;
		ConstIterator end() const noexcept;
		ConstIterator cend() const noexcept;
		
		char& at(size_t position);
		const char& at(size_t position) const;
		char& operator[](size_t position) noexcept;
		const char& operator[](size_t position) const noexcept;
		
		size_t length() const noexcept;
		size_t size() const noexcept;
		size_t max_size() const noexcept;
		
	private:
		char* m_buffer{ nullptr };
		size_t m_size{ 0 };
	};
}
