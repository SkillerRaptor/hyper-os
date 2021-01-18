#pragma once

#include <LibC/stdlib.h>

class String
{
private:
	char* m_Buffer;
	size_t m_Size;

public:
	String();
	String(const char* buffer);
	String(const String& string);
	String& operator=(const String& string);
	String(String&& string);
	String& operator=(String&& string);
	~String();

	size_t size() const;
	size_t length() const;
	void clear();
	bool empty() const;

	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	char& at(size_t pos);
	const char& at(size_t pos) const;
	char& back();
	const char& back() const;
	char& front();
	const char& front() const;

	const char* c_str() const;
	const char* data() const;

	String operator+(const String& string);
};