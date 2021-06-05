#pragma once

#include <AK/Assertion.hpp>
#include <AK/Iterator.hpp>
#include <AK/Logger.hpp>
#include <AK/Utility.hpp>

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
		Vector()
		{
			reallocate(2);
		}
		
		~Vector()
		{
			clear();
			delete[] m_data;
		}
		
		void push_back(const T& value)
		{
			if (m_size >= m_capacity)
			{
				reallocate(m_capacity + m_capacity / 2);
			}
			
			m_data[m_size] = value;
			++m_size;
		}
		
		void push_back(T&& value)
		{
			if (m_size >= m_capacity)
			{
				reallocate(m_capacity + m_capacity / 2);
			}
			
			m_data[m_size] = move(value);
			++m_size;
		}
		
		template <typename... Args>
		T& emplace_back(Args&& ... args)
		{
			if (m_size >= m_capacity)
			{
				reallocate(m_capacity + m_capacity / 2);
			}
			
			new (&m_data[m_size]) T(forward<Args>(args)...);
			return m_data[m_size++];
		}
		
		void pop_back()
		{
			if (m_size > 0)
			{
				--m_size;
				m_data[m_size].~T();
			}
		}
		
		void clear()
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i].~T();
			}
			
			m_size = 0;
		}
		
		void reserve(size_t capacity)
		{
			reallocate(capacity);
		}
		
		void resize(size_t size)
		{
			// TODO: Implement resize!
		}
		
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
		void reallocate(size_t capacity)
		{
			T* data = new T[capacity];
			
			if (capacity < m_size)
			{
				m_size = capacity;
			}
			
			for (size_t i = 0; i < m_size; ++i)
			{
				data[i] = move(m_data[i]);
			}
			
			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i].~T();
			}
			
			delete[] m_data;
			m_data = data;
			m_capacity = capacity;
		}
	
	private:
		Pointer m_data{ nullptr };
		SizeType m_size{ 0 };
		SizeType m_capacity{ 0 };
	};
}
