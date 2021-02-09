#include <AK/String.h>

#include <AK/Exception.h>
#include <AK/StringBuilder.h>
#include <LibC/string.h>

namespace AK
{
	String::String()
		: m_Buffer(nullptr), m_Size(0)
	{
	}

	String::String(const char buffer)
	{
		m_Size = 1;
		m_Buffer = new char[2];
		m_Buffer[0] = buffer;
		m_Buffer[m_Size] = '\0';
	}

	String::String(const char* buffer)
	{
		m_Size = strlen(buffer);
		m_Buffer = new char[m_Size + 1];
		strncpy(m_Buffer, buffer, m_Size);
		m_Buffer[m_Size] = '\0';
	}

	String::String(const String& string)
	{
		m_Size = string.m_Size;
		m_Buffer = new char[m_Size + 1];
		strncpy(m_Buffer, string.m_Buffer, m_Size);
		m_Buffer[m_Size] = '\0';
	}

	String& String::operator=(const String& string)
	{
		if (m_Buffer)
			delete[] m_Buffer;
		m_Size = 0;

		m_Size = string.m_Size;
		m_Buffer = new char[m_Size + 1];
		strncpy(m_Buffer, string.m_Buffer, m_Size);
		m_Buffer[m_Size] = '\0';
		return *this;
	}

	String::String(String&& string)
	{
		m_Size = string.m_Size;
		m_Buffer = string.m_Buffer;
		string.m_Buffer = nullptr;
	}

	String& String::operator=(String&& string)
	{
		if (m_Buffer)
			delete[] m_Buffer;
		m_Size = 0;

		m_Size = string.m_Size;
		m_Buffer = string.m_Buffer;
		string.m_Buffer = nullptr;
		return *this;
	}

	String::~String()
	{
		if (m_Buffer)
			delete[] m_Buffer;
		m_Size = 0;
	}

	size_t String::size() const
	{
		return m_Size;
	}

	size_t String::length() const
	{
		return m_Size;
	}

	void String::resize(size_t n)
	{
		char* buffer = new char[n + 1];
		strncpy(buffer, m_Buffer, m_Size);
		m_Buffer = buffer;
		m_Buffer[n] = '\0';
		m_Size = n;
	}

	void String::clear()
	{
		if (m_Buffer)
			delete[] m_Buffer;
		m_Size = 0;
	}

	bool String::empty() const
	{
		return m_Size == 0;
	}

	char& String::operator[](size_type pos)
	{
		return m_Buffer[pos];
	}

	const char& String::operator[](size_type pos) const
	{
		return m_Buffer[pos];
	}

	char& String::at(size_type pos)
	{
		return m_Buffer[pos];
	}

	const char& String::at(size_type pos) const
	{
		return m_Buffer[pos];
	}

	char& String::back()
	{
		return m_Buffer[m_Size - 1];
	}

	const char& String::back() const
	{
		return m_Buffer[m_Size - 1];
	}

	char& String::front()
	{
		return m_Buffer[0];
	}

	const char& String::front() const
	{
		return m_Buffer[0];
	}

	const char* String::c_str() const
	{
		return m_Buffer;
	}

	const char* String::data() const
	{
		return m_Buffer;
	}

	String String::operator+(const String& string)
	{
		String s;
		s.m_Size = m_Size + string.m_Size;
		s.m_Buffer = new char[s.m_Size + 1];
		strncpy(s.m_Buffer, m_Buffer, m_Size);
		strncpy(s.m_Buffer + m_Size, string.m_Buffer, string.m_Size);

		return s;
	}

	int stoi(const String& string, size_t position, int base)
	{
		//if(string.empty())
		//	throw Exception("Invalid string argument, string was empty");

		bool negative = (string[position] == '-');
		if (string[position] == '+' || string[position] == '-')
			position++;

		int result = 0;
		for (size_t i = position; i < string.length(); i++)
		{
			char c = string[position];
			//if (c < '0' || c > '9')
			//	throw Exception("Invalid input string");
			result = result * base - (c - static_cast<char>('0'));
			position++;
		}

		return negative ? result : -result;
	}

	long stol(const String& string, size_t position, int base)
	{
		//if (string.empty())
		//	throw Exception("Invalid string argument, string was empty");

		bool negative = (string[position] == '-');
		if (string[position] == '+' || string[position] == '-')
			position++;

		long result = 0;
		for (size_t i = position; i < string.length(); i++)
		{
			char c = string[position];
			//if (c < '0' || c > '9')
			//	throw Exception("Invalid input string");
			result = result * base - (c - static_cast<char>('0'));
			position++;
		}

		return negative ? result : -result;
	}

	long long stoll(const String& string, size_t position, int base)
	{
		//if (string.empty())
		//	throw Exception("Invalid string argument, string was empty");

		bool negative = (string[position] == '-');
		if (string[position] == '+' || string[position] == '-')
			position++;

		long long result = 0;
		for (size_t i = position; i < string.length(); i++)
		{
			char c = string[position];
			//if (c < '0' || c > '9')
			//	throw Exception("Invalid input string");
			result = result * base - (c - static_cast<char>('0'));
			position++;
		}

		return negative ? result : -result;
	}

	String to_string(int8_t value)
	{
		String string{};
		string.resize(128);

		bool isNegative{ false };
		if (value < 0)
		{
			isNegative = true;
			value *= -1;
			string[0] = '-';
		}

		uint8_t size{ 0 };
		uint8_t sizeTest{ static_cast<uint8_t>(value) };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[isNegative + size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[isNegative + size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(int16_t value)
	{
		String string{};
		string.resize(128);

		bool isNegative{ false };
		if (value < 0)
		{
			isNegative = true;
			value *= -1;
			string[0] = '-';
		}

		uint8_t size{ 0 };
		uint16_t sizeTest{ static_cast<uint16_t>(value) };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[isNegative + size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[isNegative + size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(int32_t value)
	{
		String string{};
		string.resize(128);

		bool isNegative{ false };
		if (value < 0)
		{
			isNegative = true;
			value *= -1;
			string[0] = '-';
		}

		uint8_t size{ 0 };
		uint32_t sizeTest{ static_cast<uint32_t>(value) };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[isNegative + size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[isNegative + size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(int64_t value)
	{
		String string{};
		string.resize(128);

		bool isNegative{ false };
		if (value < 0)
		{
			isNegative = true;
			value *= -1;
			string[0] = '-';
		}

		uint8_t size{ 0 };
		uint64_t sizeTest{ static_cast<uint64_t>(value) };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[isNegative + size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[isNegative + size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(uint8_t value)
	{
		String string{};
		string.resize(128);

		uint8_t size{ 0 };
		uint8_t sizeTest{ value };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(uint16_t value)
	{
		String string{};
		string.resize(128);

		uint8_t size{ 0 };
		uint16_t sizeTest{ value };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(uint32_t value)
	{
		String string{};
		string.resize(128);

		uint8_t size{ 0 };
		uint32_t sizeTest{ value };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	String to_string(uint64_t value)
	{
		String string{};
		string.resize(128);

		uint8_t size{ 0 };
		uint64_t sizeTest{ value };
		while ((sizeTest / 10) > 0)
		{
			sizeTest /= 10;
			size++;
		}

		uint8_t index{ 0 };
		uint8_t remainder{ 0 };
		while ((value / 10) > 0)
		{
			remainder = value % 10;
			value /= 10;
			string[size - index] = static_cast<char>('0' + remainder);
			index++;
		}
		remainder = value % 10;
		string[size - index] = static_cast<char>('0' + remainder);
		return string;
	}

	// TODO: SSE
	/*
	String to_string(float value)
	{
		String intString = to_string(static_cast<int64_t>(value));

		if (value < 0)
			value *= -1;

		uint64_t place = intString.length();
		String string{ intString };
		string.resize(128);
		string[place++] = '.';

		float newValue = value - static_cast<int64_t>(value);
		while (newValue >= 0.0000001)
		{
			newValue *= 10;
			string[place++] = static_cast<int64_t>(newValue) + static_cast<char>('0');
			newValue -= static_cast<int64_t>(newValue);
		}

		return string;
	}
	*/

	// TODO: SSE
	/*
	String to_string(double value)
	{
		String intString = to_string(static_cast<int64_t>(value));

		if (value < 0)
			value *= -1;

		uint64_t place = intString.length();
		String string{ intString };
		string.resize(128);
		string[place++] = '.';

		double newValue = value - static_cast<int64_t>(value);
		while (newValue >= 0.0000001)
		{
			newValue *= 10;
			string[place++] = static_cast<int64_t>(newValue) + static_cast<char>('0');
			newValue -= static_cast<int64_t>(newValue);
		}

		return string;
	}
	*/

	// TODO: SSE
	/*
	String to_string(long double value)
	{
		String intString = to_string(static_cast<int64_t>(value));

		if (value < 0)
			value *= -1;

		uint64_t place = intString.length();
		String string{ intString };
		string.resize(128);
		string[place++] = '.';

		long double newValue = value - static_cast<int64_t>(value);
		while (newValue >= 0.0000001)
		{
			newValue *= 10;
			string[place++] = static_cast<int64_t>(newValue) + static_cast<char>('0');
			newValue -= static_cast<int64_t>(newValue);
		}

		return string;
	}
	*/

	String to_hex_string(uint64_t value)
	{
		StringBuilder builder;

		int ret = 0;
		int fieldWidth = 16;

		int digits = 0;
		for (uint64_t n = value; n > 0; n >>= 4)
			++digits;
		if (digits == 0)
			digits = 1;

		builder.append("0x");
		ret += 2;
		fieldWidth += 2;

		while (ret < fieldWidth - digits)
		{
			builder.append("0");
			++ret;
		}

		static constexpr const char* hex_digits = "0123456789ABCDEF";
		if (value == 0)
		{
			builder.append("0");
		}
		else
		{
			uint8_t shiftCount = digits * 4;
			while (shiftCount)
			{
				shiftCount -= 4;
				builder.append(hex_digits[(value >> shiftCount) & 0x0F]);
				++ret;
			}
		}
		builder.append("\0");

		return builder.build();
	}
}