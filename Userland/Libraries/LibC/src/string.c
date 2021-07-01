/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <string.h>

char* strcpy(char* destination, const char* source)
{
	size_t i;

	for (i = 0; source[i] != '\0'; ++i)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';
}

char* strncpy(char* destination, const char* source, size_t length)
{
	size_t i;

	for (i = 0; i < length && source[i] != '\0'; ++i)
	{
		destination[i] = source[i];
	}

	for (; i < length; ++i)
	{
		destination[i] = '\0';
	}

	return destination;
}

size_t strlen(const char* string)
{
	size_t i = 0;

	while (string[i] != '\0')
	{
		++i;
	}

	return i;
}

int memcmp(const void* source1, const void* source2, size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		if (*((uint8_t*) source1 + i) < *((uint8_t*) source2 + i))
		{
			return -1;
		}
		
		if (*((uint8_t*) source1 + i) > *((uint8_t*) source2 + i))
		{
			return 1;
		}
	}
	return 0;
}

void* memset(void* destination, int value, size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		*((uint8_t*) destination + i) = value;
	}
	
	return destination;
}

void* memcpy(void* destination, const void* source, size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		*((uint8_t*) destination + i) = *((uint8_t*) source + i);
	}
	
	return destination;
}

void* memmove(void* destination, const void* source, size_t count)
{
	if (source > destination)
	{
		for (int i = 0; i < count; ++i)
		{
			*((uint8_t*) destination + i) = *((uint8_t*) source + i);
		}
	}
	else
	{
		for (int i = count - 1; i >= 0; --i)
		{
			*((uint8_t*) destination + i) = *((uint8_t*) source + i);
		}
	}
	
	return destination;
}
