#pragma once

#include <AK/String.hpp>
#include <AK/Vector.h>

class StringBuilder
{
private:
	Vector<String> m_Strings;

public:
	StringBuilder() = default;
	~StringBuilder() = default;

	void append(String& string);
	void append(const String& string);
	void append(const char string);
	void append(const char* string);

	void clear();

	String build();
};