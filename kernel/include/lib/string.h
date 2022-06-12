/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *string);
int strncmp(const char *string1, const char *string2, size_t count);
char *strtok(char *string, const char *delimiters);

uint64_t stroull(const char *string, char **end, int base);

int isalpha(int character);
int isdigit(int character);
int isspace(int character);
int isupper(int character);
