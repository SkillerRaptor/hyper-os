#pragma once

#include <AK/NonCopyable.h>
#include <LibC/stddef.h>
#include <LibC/stdint.h>

class Bitmap : public NonCopyable
{
private:
	static constexpr uint16_t ByteSize = 8;

	uint8_t* m_Data;
	size_t m_Size;

public:
	Bitmap(uint8_t* data = nullptr, uint64_t size = 0);

	void SetBit(uint64_t index, bool value);
	bool GetBit(uint64_t index);

	void SetSize(uint64_t size);
	uint64_t GetSize() const;

	void SetData(uint8_t* data);
	uint8_t* GetData();
	const uint8_t* GetData() const;

	bool operator[](size_t index) const;
};