#include "String.h"

#include <LibC/string.h>

String::String()
	: m_Buffer(nullptr), m_Size(0)
{
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

char& String::operator[](size_t pos)
{
	return m_Buffer[pos];
}

const char& String::operator[](size_t pos) const
{
	return m_Buffer[pos];
}

char& String::at(size_t pos)
{
	return m_Buffer[pos];
}

const char& String::at(size_t pos) const
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