#pragma once

#include <AK/NonCopyable.h>
#include <LibC/stddef.h>
#include <LibC/stdint.h>

namespace AK
{
	class Bitmap : public NonCopyable
	{
	private:
		static constexpr uint16_t ByteSize = 8;

		uint8_t* m_Data;
		size_t m_Size;

	public:
		Bitmap(uint8_t* data = nullptr, uint64_t size = 0);

		void set_bit(uint64_t index, bool value);
		bool get_bit(uint64_t index);

		void set_size(size_t size);
		size_t size() const;

		void set_data(uint8_t* data);
		uint8_t* data();
		const uint8_t* data() const;

		bool operator[](size_t index) const;
	};
}