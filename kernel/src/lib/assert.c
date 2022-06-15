/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/assert.h"

#include "lib/stacktrace.h"
#include "lib/logger.h"
#include "scheduling/spinlock.h"

static struct spinlock s_lock = { 0 };

__attribute__((noreturn)) void __assertion_failed(
	const char *assertion,
	const char *file,
	unsigned int line,
	const char *function)
{
	spinlock_lock(&s_lock);
		
	logger_error("");
	logger_error("Assertion '%s' failed in %s at %s:%u", assertion, function, file, line);
	logger_error("");
	stacktrace_print(50);
	logger_error("");

	spinlock_unlock(&s_lock);

	for (;;)
	{
		__asm__ __volatile__("cli");
		__asm__ __volatile__("hlt");
	}
}
