#include "Bitmap.h"

#include <LibC/stdio.h>

Bitmap::Bitmap(uint8_t* data, uint64_t size)
	: m_Data(data), m_Size(size)
{
}

void Bitmap::SetBit(uint64_t index, bool value)
{
	// TODO: ASSERT(index < m_Size, "Index is outside of Bitmap Size");
	if (value)
		m_Data[index / ByteSize] |= static_cast<uint8_t>((1u << (index % ByteSize)));
	else
		m_Data[index / ByteSize] &= static_cast<uint8_t>(~(1u << (index % ByteSize)));
}

bool Bitmap::GetBit(uint64_t index)
{
	// TODO: ASSERT(index < m_Size, "Index is outside of Bitmap Size");
	return 0 != (m_Data[index / ByteSize] & (1u << (index % ByteSize)));
}

void Bitmap::Print(uint64_t start, uint64_t length)
{
	for (uint64_t i = start; i < start + length; i++)
		printf("\n%d\n", i);
}

uint8_t* Bitmap::Data()
{
	return m_Data;
}

const uint8_t* Bitmap::Data() const
{
	return m_Data;
}

uint64_t Bitmap::Size() const
{
	return m_Size;
}