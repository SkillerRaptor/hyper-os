#pragma once

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
	
	public:
		String() = default;
		
	private:
		char* m_buffer{ nullptr };
		size_t m_size{ 0 };
	};
}
