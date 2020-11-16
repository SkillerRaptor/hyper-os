#pragma once

#include <AK/NonCopyable.h>
#include <LibC/stdint.h>

class Bitmap : public NonCopyable
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

	void SetData(uint8_t* data);
	uint8_t* Data();
	const uint8_t* Data() const;

	void SetSize(uint64_t size);
	uint64_t Size() const;
};