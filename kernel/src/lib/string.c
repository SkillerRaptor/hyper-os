/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/string.h"

#include <stdbool.h>

#define ULLONG_MAX 18446744073709551615ULL

static bool is_delimiter(char character, const char *delimiters);

size_t strlen(const char *string)
{
	if (string == NULL)
	{
		return 0;
	}

	size_t i = 0;
	while (string[i] != '\0')
	{
		++i;
	}

	return i;
}

int strncmp(const char *string1, const char *string2, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		const char first_char = string1[i];
		const char second_char = string2[i];

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

char *strtok(char *string, const char *delimiters)
{
	static char *backup_string = NULL;
	if (string == NULL)
	{
		string = backup_string;
	}

	if (string == NULL)
	{
		return NULL;
	}

	for (;;)
	{
		if (is_delimiter(*string, delimiters))
		{
			string++;
			continue;
		}

		if (*string == '\0')
		{
			return NULL;
		}

		break;
	}

	char *return_string = string;
	for (;;)
	{
		if (*string == '\0')
		{
			backup_string = string;
			return return_string;
		}

		if (is_delimiter(*string, delimiters))
		{
			*string = '\0';
			backup_string = string + 1;
			return return_string;
		}

		string++;
	}
}

int isalpha(int character)
{
	return (character >= 'a' && character <= 'z') ||
				 (character >= 'A' && character <= 'Z');
}

int isdigit(int character)
{
	return character >= '0' && character <= '9';
}

int isspace(int character)
{
	return character == ' ';
}

int isupper(int character)
{
	return character >= 'A' && character <= 'Z';
}

uint64_t stroull(const char *string, char **endptr, int base)
{
	char character = '\0';
	do
	{
		character = *string++;
	} while (isspace(character));

	bool is_negative = false;
	if (character == '-')
	{
		is_negative = true;
		character = *string++;
	}

	if (
		(base == 0 || base == 16) && character == '0' &&
		(*string == 'x' || *string == 'X'))
	{
		character = string[1];
		string += 2;
		base = 16;
	}

	if (base == 0)
	{
		base = character == '0' ? 8 : 10;
	}

	uint64_t acc = 0;
	int64_t any = 0;

	const uint64_t cutoff = ULLONG_MAX / base;
	const int64_t cutlim = ULLONG_MAX % base;
	for (acc = 0, any = 0;; character = *string++)
	{
		if (isdigit(character))
		{
			character -= '0';
		}
		else if (isalpha(character))
		{
			character -= isupper(character) ? 'A' - 10 : 'a' - 10;
		}
		else
		{
			break;
		}

		if (character >= base)
		{
			break;
		}

		if (any < 0 || acc > cutoff || (acc == cutoff && character > cutlim))
		{
			any = -1;
			continue;
		}

		any = 1;
		acc *= base;
		acc += character;
	}

	if (any < 0)
	{
		acc = ULLONG_MAX;
	}
	else if (is_negative)
	{
		acc = -acc;
	}

	if (endptr != 0)
	{
		*endptr = (char *) (any ? string - 1 : string);
	}

	return acc;
}

static bool is_delimiter(char character, const char *delimiters)
{
	while (*delimiters != '\0')
	{
		if (character == *delimiters)
		{
			return true;
		}

		delimiters++;
	}

	return false;
}
