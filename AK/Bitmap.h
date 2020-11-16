#pragma once

#include <LibC/stdint.h>

class Bitmap
{
private:
	static constexpr uint16_t ByteSize = 8;

	uint8_t* m_Data;
	uint64_t m_Size;

public:
	Bitmap(uint8_t* data, uint64_t size);

	void SetBit(uint64_t index, bool value);
	bool GetBit(uint64_t index);

	void Print(uint64_t start, uint64_t length);

	uint8_t* Data();
	const uint8_t* Data() const;
	uint64_t Size() const;
};