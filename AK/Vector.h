#pragma once

#include <AK/Utility.h>

template<typename T>
class Vector
{
private:
	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;

public:
	Vector()
	{
		reallocate(2);
	}

	~Vector()
	{
		clear();
		delete[] m_Data;
	}

	void push_back(const T& value)
	{
		if (m_Size >= m_Capacity)
			reallocate(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = value;
		m_Size++;
	}

	void push_back(T&& value)
	{
		if (m_Size >= m_Capacity)
			reallocate(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = move(value);
		m_Size++;
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			reallocate(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = new T(forward<Args>(args)...);
		return m_Data[m_Size++];
	}

	void pop_back()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		m_Size = 0;
	}

	T& operator[](size_t pos)
	{
		return m_Data[pos];
	}

	const T& operator[](size_t pos) const
	{
		return m_Data[pos];
	}

private:
	void reallocate(size_t new_capacity)
	{
		T* new_block = new T[new_capacity];

		size_t size = m_Size;
		if (new_capacity < size)
			size = new_capacity;

		for (size_t i = 0; i < size; i++)
			new_block[i] = move(m_Data[i]);

		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		delete[] m_Data;
		m_Data = new_block;
		m_Capacity = new_capacity;
	}
};