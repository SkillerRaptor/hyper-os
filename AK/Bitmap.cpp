#include <AK/Bitmap.h>

#include <stdio.h>
#include <AK/Panic.h>
#include <Kernel/Memory/MemoryDefines.h>

Bitmap::Bitmap(uint8_t* data, uint64_t size)
	: m_Data(data), m_Size(size)
{
}

void Bitmap::set_bit(uint64_t index, bool value)
{
	if (index < m_Size)
		panic("Bitmap: Index is out of range!");
	if (value)
		m_Data[index / BYTE_SIZE] |= static_cast<uint8_t>((1u << (index % BYTE_SIZE)));
	else
		m_Data[index / BYTE_SIZE] &= static_cast<uint8_t>(~(1u << (index % BYTE_SIZE)));
}

bool Bitmap::get_bit(uint64_t index)
{
	if (index < m_Size)
		panic("Bitmap: Index is out of range!");
	return 0 != (m_Data[index / BYTE_SIZE] & (1u << (index % BYTE_SIZE)));
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
	return (0 != (m_Data[index / BYTE_SIZE] & (1u << (index % BYTE_SIZE))));
}