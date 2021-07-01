/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_ASSERT_H_
#define HYPEROS_LIBC_ASSERT_H_

#include <stdlib.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef NDEBUG
#	ifndef assert
#		define assert(x)                                            \
			do                                                       \
			{                                                        \
				if (!(x))                                            \
				{                                                    \
					printf(                                          \
						"assert: %s:%s: %s: Assertion '%s' failed.", \
						__builtin_FILE(),                            \
						__builtin_FUNCTION(),                        \
						__builtin_LINE(),                            \
						x);                                          \
					abort();                                         \
				}                                                    \
			} while (0)
#	endif
#endif

__END_DECLS

#endif // HYPEROS_LIBC_ASSERT_H_
