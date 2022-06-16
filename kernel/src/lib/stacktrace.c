/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/stacktrace.h"

#include "arch/boot.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/math.h"
#include "lib/memory.h"
#include "lib/string.h"
#include "memory/kmalloc.h"
#include "memory/pmm.h"
#include "scheduling/spinlock.h"

#include <stdint.h>

struct stack_frame
{
	struct stack_frame *rbp;
	uint64_t rip;
};

struct symbol
{
	char name[100];
	uintptr_t address;
};

static size_t s_symbol_count = 0;
static struct symbol *s_symbols = NULL;
static struct spinlock s_lock = { 0 };

void stacktrace_init(void)
{
	struct limine_module_response *module_response = boot_get_modules();
	assert(module_response != NULL);

	struct limine_file *file = module_response->modules[0];
	assert(file != NULL);

	logger_info(
		"Stacktrace: Kernel symbol map found at 0x%016x",
		(uintptr_t) file->address);

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

	char **symbol_map_lines = kmalloc(sizeof(char *) * s_symbol_count);

	size_t current_symbol = 0;
	char *symbol_map_line = strtok(symbol_map, "\n");
	while (symbol_map_line != NULL)
	{
		const size_t line_length = strlen(symbol_map_line);

		symbol_map_lines[current_symbol] = kmalloc(sizeof(char) * line_length);
		memcpy(symbol_map_lines[current_symbol], symbol_map_line, line_length);

		++current_symbol;

		symbol_map_line = strtok(NULL, "\n");
	}

	kfree(symbol_map);

	for (size_t i = 0; i < s_symbol_count; ++i)
	{
		char *symbol_line = symbol_map_lines[i];

		size_t part_index = 0;
		char *symbol_part = strtok(symbol_line, " ");
		while (symbol_part != NULL)
		{
			if (part_index == 0)
			{
				s_symbols[i].address = stroull(symbol_part, NULL, 16);
			}

			if (part_index == 2)
			{
				memcpy(s_symbols[i].name, symbol_part, strlen(symbol_part));
			}

			++part_index;

			symbol_part = strtok(NULL, " ");
		}

		kfree(symbol_line);
	}

	kfree(symbol_map_lines);

	logger_info("Stacktrace: Symbol map parsed");

	const size_t page_count = DIV_ROUND_UP(file->size, PAGE_SIZE);
	pmm_free((void *) (file->address - pmm_get_memory_offset()), page_count);
	logger_info("Stacktrace: %u pages were freed", page_count);

	logger_info("Stacktrace: Initialized", DIV_ROUND_UP(file->size, PAGE_SIZE));
}

void stacktrace_print(size_t max_frames)
{
	spinlock_lock(&s_lock);

	struct stack_frame *stack_frame = NULL;
	__asm__ __volatile__("mov %%rbp, %0" : "=r"(stack_frame) : : "memory");

	logger_error("Stacktrace:");
	for (size_t i = 0; stack_frame != NULL && i < max_frames; ++i)
	{
		const uint64_t rip = stack_frame->rip;
		if (rip == 0)
		{
			break;
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
			logger_error(" %u. ?? <0x%016x>", i + 1, rip);
			continue;
		}

		logger_error(" %u. %s <0x%016x>", i + 1, symbol->name, rip);
	}

	spinlock_unlock(&s_lock);
}
