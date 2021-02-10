#pragma once

#include <stddef.h>

template<typename T, size_t S>
class Array
{
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

private:
	T m_Data[S];

public:
	T& at(size_t pos)
	{
		return m_Data[pos];
	}

	const T& at(size_t pos) const
	{
		return m_Data[pos];
	}

	T& operator[](size_t pos)
	{
		return m_Data[pos];
	}

	const T& operator[](size_t pos) const
	{
		return m_Data[pos];
	}

	T* data()
	{
		return m_Data;
	}

	const T* data()
	{
		return m_Data;
	}

	constexpr size_t size() const
	{
		return S;
	}
};