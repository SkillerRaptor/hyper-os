/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifdef NDEBUG
#	define assert(assertion) ((void) 0)
#else
#	define assert(assertion)                                           \
		do                                                                \
		{                                                                 \
			if (!(assertion))                                               \
			{                                                               \
				__assertion_failed(#assertion, __FILE__, __LINE__, __func__); \
			}                                                               \
		} while (0)
#endif

__attribute__((noreturn)) void __assertion_failed(
	const char *assertion,
	const char *file,
	unsigned int line,
	const char *function);
