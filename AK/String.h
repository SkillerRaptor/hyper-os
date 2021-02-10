#pragma once

#include <stdlib.h>

class String
{
public:
	using size_type = size_t;

private:
	char* m_Buffer;
	size_t m_Size;

public:
	String();
	String(const char buffer);
	String(const char* buffer);
	String(const String& string);
	String& operator=(const String& string);
	String(String&& string);
	String& operator=(String&& string);
	~String();

	size_t size() const;
	size_t length() const;
	void resize(size_t n);
	void clear();
	bool empty() const;

	char& operator[](size_type pos);
	const char& operator[](size_type pos) const;
	char& at(size_type pos);
	const char& at(size_type pos) const;
	char& back();
	const char& back() const;
	char& front();
	const char& front() const;

	const char* c_str() const;
	const char* data() const;

	String operator+(const String& string);
};

int stoi(const String& string, size_t position = 0, int base = 10);
long stol(const String& string, size_t position = 0, int base = 10);
long long stoll(const String& string, size_t position = 0, int base = 10);

String to_string(int8_t value);
String to_string(int16_t value);
String to_string(int32_t value);
String to_string(int64_t value);
String to_string(uint8_t value);
String to_string(uint16_t value);
String to_string(uint32_t value);
String to_string(uint64_t value);
String to_hex_string(uint64_t value);