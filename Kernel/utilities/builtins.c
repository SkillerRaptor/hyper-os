#include "builtins.h"

#include <stdint.h>

void* memcpy(void* destination, const void* source, size_t n)
{
	uint8_t* _destination = (uint8_t*) destination;
	const uint8_t* _source = (const uint8_t*) source;
	
	for (size_t i = 0; i < n; i++)
	{
		_destination[i] = _source[i];
	}
	
	return destination;
}

void* memset(void* destination, int value, size_t n)
{
	uint8_t* _destination = (uint8_t*) destination;
	
	for (size_t i = 0; i < n; i++)
	{
		_destination[i] = (uint8_t) value;
	}
	
	return destination;
}

void* memmove(void* destination, const void* source, size_t n)
{
	uint8_t* _destination = (uint8_t*) destination;
	const uint8_t* _source = (const uint8_t*) source;
	
	if (source > destination)
	{
		for (size_t i = 0; i < n; i++)
		{
			_destination[i] = _source[i];
		}
	}
	else if (source < destination)
	{
		for (size_t i = n; i > 0; i--)
		{
			_destination[i - 1] = _source[i - 1];
		}
	}
	
	return destination;
}

int memcmp(const void* first, const void* second, size_t n)
{
	const uint8_t* _first = (const uint8_t*) first;
	const uint8_t* _second = (const uint8_t*) second;
	
	for (size_t i = 0; i < n; i++)
	{
		if (_first[i] != _second[i])
		{
			return _first[i] < _second[i] ? -1 : 1;
		}
	}
	
	return 0;
}

char* strcpy(char* destination, const char* source)
{
	size_t i;
	
	for (i = 0; source[i]; i++)
	{
		destination[i] = source[i];
	}
	destination[i] = 0;
	
	return destination;
}

char* strncpy(char* destination, const char* source, size_t n)
{
	size_t i;
	
	for (i = 0; i < n && source[i]; i++)
	{
		destination[i] = source[i];
	}
	for (; i < n; i++)
	{
		destination[i] = 0;
	}
	
	return destination;
}

int strcmp(const char* first, const char* second)
{
	for (size_t i = 0; ; i++)
	{
		char first_char = first[i];
		char second_char = second[i];
		if (first_char != second_char)
		{
			return first_char - second_char;
		}
		if (!first_char)
		{
			return 0;
		}
	}
}

int strncmp(const char* first, const char* second, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		char first_char = first[i];
		char second_char = second[i];
		if (first_char != second_char)
		{
			return first_char - second_char;
		}
		if (!first_char)
		{
			return 0;
		}
	}
	
	return 0;
}

size_t strlen(const char* string)
{
	size_t length;
	for (length = 0; string[length]; length++);
	return length;
}
