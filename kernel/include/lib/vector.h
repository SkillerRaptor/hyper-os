/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "memory/kmalloc.h"

#include <stddef.h>

#define VECTOR_TYPE(type) type *

#define VECTOR_FREE(vector)                 \
	do                                        \
	{                                         \
		if (vector == NULL)                     \
		{                                       \
			break;                                \
		}                                       \
                                            \
		size_t *ptr = &((size_t *) vector)[-2]; \
		kfree(ptr);                             \
	} while (0)

#define VECTOR_SET_CAPACITY(vector, size) \
	do                                      \
	{                                       \
		if (vector == NULL)                   \
		{                                     \
			break;                              \
		}                                     \
                                          \
		((size_t *) vector)[-1] = size;       \
	} while (0)

#define VECTOR_GET_CAPACITY(vector) \
	(vector == NULL ? 0 : ((size_t *) vector)[-1])

#define VECTOR_SET_SIZE(vector, size) \
	do                                  \
	{                                   \
		if (vector == NULL)               \
		{                                 \
			break;                          \
		}                                 \
                                      \
		((size_t *) vector)[-2] = size;   \
	} while (0)

#define VECTOR_GET_SIZE(vector) (vector == NULL ? 0 : ((size_t *) vector)[-2])

#define VECTOR_IS_EMPTY(vector) (VECTOR_GET_SIZE(vector) == 0)

#define VECTOR_COMPUTE_GROW_SIZE(size) (size == 0 ? 1 : (size << 1))

#define VECTOR_GROW(vector, size)                                          \
	do                                                                       \
	{                                                                        \
		const size_t new_size = size * sizeof(*vector) + (sizeof(size_t) * 2); \
		if (vector == NULL)                                                    \
		{                                                                      \
			size_t *ptr = kmalloc(new_size);                                     \
			vector = (void *) &ptr[2];                                           \
			VECTOR_SET_CAPACITY(vector, size);                                   \
			VECTOR_SET_SIZE(vector, 0);                                          \
		}                                                                      \
                                                                           \
		size_t *ptr = &((size_t *) vector)[-2];                                \
		size_t *new_ptr = krealloc(ptr, new_size);                             \
		vector = (void *) &new_ptr[2];                                         \
		VECTOR_SET_CAPACITY(vector, size);                                     \
	} while (0)

#define VECTOR_PUSH_BACK(vector, value)                        \
	do                                                           \
	{                                                            \
		const size_t capacity = VECTOR_GET_CAPACITY(vector);       \
		if (capacity <= VECTOR_GET_SIZE(vector))                   \
		{                                                          \
			VECTOR_GROW(vector, VECTOR_COMPUTE_GROW_SIZE(capacity)); \
		}                                                          \
                                                               \
		const size_t size = VECTOR_GET_SIZE(vector);               \
		vector[size] = value;                                      \
		VECTOR_SET_SIZE(vector, size + 1);                         \
	} while (0)

#define VECTOR_POP_BACK(vector)                           \
	do                                                      \
	{                                                       \
		VECTOR_SET_SIZE(vector, VECTOR_GET_SIZE(vector) - 1); \
	} while (0)
