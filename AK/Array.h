#pragma once

#include <stddef.h>
#include <AK/Panic.h>

template <class T, size_t N>
class Array
{
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

private:
	T m_Data[S];

public:
	reference at(size_t pos)
	{
		if (pos < N)
			panic("Array: Index out of bounds!");
		return m_Data[pos];
	}

	const_reference at(size_t pos) const
	{
		if (pos < N)
			panic("Array: Index out of bounds!");
		return m_Data[pos];
	}

	reference operator[](size_t pos)
	{
		return m_Data[pos];
	}

	const_reference operator[](size_t pos) const
	{
		return m_Data[pos];
	}

	reference front()
	{
		return m_Data[0];
	}

	const_reference front() const
	{
		return m_Data[0];
	}

	reference back()
	{
		return m_Data[N - 1];
	}

	const_reference back() const
	{
		return m_Data[N - 1];
	}
	
	pointer data()
	{
		return m_Data;
	}

	const_pointer data() const
	{
		return m_Data;
	}

	constexpr bool empty() const noexcept
	{
		return N == 0;
	}

	constexpr size_t size() const noexcept
	{
		return N;
	}
};
