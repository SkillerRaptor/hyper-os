/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/stacktrace.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/memory.h"
#include "lib/string.h"
#include "memory/kmalloc.h"

#include <stdint.h>

struct stack_frame
{
	struct stack_frame *rbp;
	uint64_t rip;
};

struct symbol
{
	uintptr_t address;
	char name[100];
};

static size_t s_symbol_count = 0;
static struct symbol *s_symbols = NULL;

void stacktrace_init(void)
{
	struct limine_module_response *module_response = boot_get_modules();
	assert(module_response != NULL);

	struct limine_file *file = module_response->modules[0];
	assert(file != NULL);

	char *symbol_map = kmalloc(sizeof(char) * file->size);
	for (size_t i = 0; i < file->size; ++i)
	{
		const char character = ((char *) file->address)[i];
		symbol_map[i] = character;

		if (character == '\n')
		{
			++s_symbol_count;
		}
	}

	s_symbols = kmalloc(sizeof(struct symbol) * s_symbol_count);

	char **symbol_lines = kmalloc(sizeof(char *) * s_symbol_count);

	size_t i = 0;
	char *line = strtok(symbol_map, "\n");
	while (line != NULL)
	{
		size_t line_length = strlen(line);
		symbol_lines[i] = kmalloc(sizeof(char) * line_length);
		memcpy(symbol_lines[i], line, line_length);

		++i;

		line = strtok(NULL, "\n");
	}

	for (size_t i = 0; i < s_symbol_count; ++i)
	{
		char *symbol_line = symbol_lines[i];

		size_t j = 0;
		char *symbol_part = strtok(symbol_line, " ");
		while (symbol_part != NULL)
		{
			if (j == 0)
			{
				s_symbols[i].address = stroull(symbol_part, NULL, 16);
			}

			if (j == 2)
			{
				memcpy(s_symbols[i].name, symbol_part, strlen(symbol_part));
			}

			++j;

			symbol_part = strtok(NULL, " ");
		}

		kfree(symbol_line);
	}

	kfree(symbol_lines);
	kfree(symbol_map);
}

void stacktrace_print(size_t max_frames)
{
	struct stack_frame *stack_frame = NULL;
	__asm__ __volatile__("mov %%rbp, %0" : "=r"(stack_frame) : : "memory");

	logger_error("Stack trace:");
	for (size_t i = 0; stack_frame != NULL && i < max_frames; ++i)
	{
		const uint64_t rip = stack_frame->rip;
		if (rip == 0)
		{
			return;
		}

		stack_frame = stack_frame->rbp;

		struct symbol *symbol = NULL;
		for (size_t j = 0; j < s_symbol_count; ++j)
		{
			if (s_symbols[j].address > rip)
			{
				break;
			}

			symbol = &s_symbols[j];
		}

		if (symbol == NULL)
		{
			continue;
		}

		logger_error("# %u 0x%016x %s", i + 1, symbol->address, symbol->name);
	}
}
