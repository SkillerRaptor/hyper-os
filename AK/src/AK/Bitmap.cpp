#include <AK/Bitmap.hpp>
#include <AK/Memory.hpp>

namespace AK
{
	Bitmap::Bitmap(SizeType size) noexcept
		: m_size{ size }
	{
	}
	
	Bitmap::Bitmap(Pointer data, SizeType size) noexcept
		: m_data{ data }
		, m_size{ size }
	{
	}
	
	Bitmap& Bitmap::set() noexcept
	{
		for (SizeType i = 0; i < m_size; i++)
		{
			m_data[i] = 0xFF;
		}
		return *this;
	}
	
	Bitmap& Bitmap::set(SizeType position, bool value)
	{
		if (position > (m_size * s_byte_size))
		{
			// TODO: Check if position is in range
			//return *this;
		}
		
		uint64_t byte_index{ position / s_byte_size };
		ValueType bit_index{ static_cast<ValueType>(position % s_byte_size) };
		ValueType bit_value{ static_cast<ValueType>(1u << (bit_index)) };
		
		if (value)
		{
			m_data[byte_index] |= bit_value;
			return *this;
		}
		
		m_data[byte_index] &= ~bit_value;
		
		return *this;
	}
	
	Bitmap& Bitmap::reset() noexcept
	{
		for (SizeType i = 0; i < m_size; i++)
		{
			m_data[i] = 0x00;
		}
		return *this;
	}
	
	Bitmap& Bitmap::reset(SizeType position)
	{
		if (position > (m_size * s_byte_size))
		{
			// TODO: Check if position is in range
			//return *this;
		}
		
		uint64_t byte_index{ position / s_byte_size };
		ValueType bit_index{ static_cast<ValueType>(position % s_byte_size) };
		ValueType bit_value{ static_cast<ValueType>(1u << (bit_index)) };
		
		m_data[byte_index] &= ~bit_value;
		
		return *this;
	}
	
	Bitmap& Bitmap::flip() noexcept
	{
		for (SizeType i = 0; i < m_size; i++)
		{
			m_data[i] = ~m_data[i];
		}
		return *this;
	}
	
	Bitmap& Bitmap::flip(SizeType position)
	{
		if (position > (m_size * s_byte_size))
		{
			// TODO: Check if position is in range
			//return *this;
		}
		
		uint64_t byte_index{ position / s_byte_size };
		ValueType bit_index{ static_cast<ValueType>(position % s_byte_size) };
		ValueType bit_value{ static_cast<ValueType>(1u << (bit_index)) };
		
		m_data[byte_index] ^= bit_value;
		return *this;
	}
	
	bool Bitmap::test(SizeType position) const noexcept
	{
		if (position > (m_size * s_byte_size))
		{
			// TODO: Check if position is in range
			//return false;
		}
		
		uint64_t byte_index{ position / s_byte_size };
		ValueType bit_index{ static_cast<ValueType>(position % s_byte_size) };
		ValueType bit_value{ static_cast<ValueType>(1u << (bit_index)) };
		
		return (m_data[byte_index] & bit_value) != 0;
	}
	
	bool Bitmap::operator[](SizeType position) const noexcept
	{
		return test(position);
	}
	
	void Bitmap::set_data(Bitmap::Pointer data) noexcept
	{
		m_data = data;
	}
	
	Bitmap::Pointer Bitmap::data() noexcept
	{
		return m_data;
	}
	
	Bitmap::ConstPointer Bitmap::data() const noexcept
	{
		return m_data;
	}
	
	void Bitmap::set_size(Bitmap::SizeType size) noexcept
	{
		m_size = size;
	}
	
	Bitmap::SizeType Bitmap::size() const noexcept
	{
		return m_size;
	}
	
	Bitmap::SizeType Bitmap::max_size() const noexcept
	{
		return m_size;
	}
}
