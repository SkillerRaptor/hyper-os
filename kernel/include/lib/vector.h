/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "lib/vector.h"
#include "scheduling/spinlock.h"

#include <stddef.h>

struct vector
{
	size_t size;
	size_t capacity;
	size_t element_size;

	void *data;

	struct spinlock lock;
};

void vector_init(struct vector *vector, size_t element_size);
void vector_destroy(struct vector *vector);

void vector_push_front(struct vector *vector, void *element);
void vector_push_back(struct vector *vector, void *element);

void vector_pop_front(struct vector *vector);
void vector_pop_back(struct vector *vector);

void vector_clear(struct vector *vector);

void *vector_get_element(struct vector *vector, size_t index);
