#include <AK/Bitmap.h>

#include <LibC/stdio.h>

namespace AK
{
	Bitmap::Bitmap(uint8_t* data, uint64_t size)
		: m_Data(data), m_Size(size)
	{
	}

	void Bitmap::set_bit(uint64_t index, bool value)
	{
		// TODO: ASSERT(index < m_Size, "Index is outside of Bitmap Size");
		if (value)
			m_Data[index / 8] |= static_cast<uint8_t>((1u << (index % 8)));
		else
			m_Data[index / 8] &= static_cast<uint8_t>(~(1u << (index % 8)));
	}

	bool Bitmap::get_bit(uint64_t index)
	{
		// TODO: ASSERT(index < m_Size, "Index is outside of Bitmap Size");
		return 0 != (m_Data[index / ByteSize] & (1u << (index % ByteSize)));
	}

	void Bitmap::set_size(size_t size)
	{
		m_Size = size;
	}

	size_t Bitmap::size() const
	{
		return m_Size;
	}

	void Bitmap::set_data(uint8_t* data)
	{
		m_Data = data;
	}

	uint8_t* Bitmap::data()
	{
		return m_Data;
	}

	const uint8_t* Bitmap::data() const
	{
		return m_Data;
	}

	bool Bitmap::operator[](size_t index) const
	{
		return (0 != (m_Data[index / ByteSize] & (1u << (index % ByteSize))));
	}
}