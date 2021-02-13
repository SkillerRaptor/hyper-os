#pragma once

#include <stddef.h>
#include <stdint.h>
#include <AK/NonCopyable.h>

class Bitmap : public NonCopyable
{
public:
	using size_type = size_t;

private:
	uint8_t* m_Data;
	size_t m_Size;

public:
	Bitmap(uint8_t* data = nullptr, size_type size = 0);

	void set_bit(size_type index, bool value);
	bool get_bit(size_type index);

	void set_size(size_type size);
	size_type size() const noexcept;

	void set_data(uint8_t* data);
	uint8_t* data();
	const uint8_t* data() const;

	bool operator[](size_type index) const;
};
