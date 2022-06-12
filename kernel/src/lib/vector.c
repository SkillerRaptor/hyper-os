/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lib/vector.h"

#include "lib/assert.h"
#include "lib/memory.h"
#include "memory/kmalloc.h"

static void vector_reallocate(struct vector *vector, size_t new_capacity);
static void *vector_get_offset(struct vector *vector, size_t index);

void vector_init(struct vector *vector, size_t element_size)
{
	assert(vector != NULL);
	assert(element_size != 0);

	vector->size = 0;
	vector->capacity = 2;
	vector->element_size = element_size;
	vector->data = kmalloc(vector->capacity * vector->element_size);

	vector_reallocate(vector, vector->capacity);
}

void vector_destroy(struct vector *vector)
{
	assert(vector != NULL);

	kfree(vector->data);
	vector->data = NULL;
}

void vector_push_front(struct vector *vector, void *element)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);
	assert(element != NULL);

	if (vector->size >= vector->capacity)
	{
		vector_reallocate(vector, vector->capacity + vector->capacity / 2);
	}

	void *ptr = vector_get_offset(vector, 0);
	memmove(ptr + vector->element_size, ptr, vector->size * vector->element_size);

	memcpy(ptr, element, vector->element_size);
	++vector->size;

	spinlock_unlock(&vector->lock);
}

void vector_push_back(struct vector *vector, void *element)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);
	assert(element != NULL);

	if (vector->size >= vector->capacity)
	{
		vector_reallocate(vector, vector->capacity + vector->capacity / 2);
	}

	void *ptr = vector_get_offset(vector, vector->size);
	memcpy(ptr, element, vector->element_size);

	++vector->size;

	spinlock_unlock(&vector->lock);
}

void vector_pop_front(struct vector *vector)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);

	void *ptr = vector_get_offset(vector, 0);
	memmove(
		ptr, ptr + vector->element_size, (vector->size - 1) * vector->element_size);

	--vector->size;

	spinlock_unlock(&vector->lock);
}

void vector_pop_back(struct vector *vector)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);
	assert(vector->size > 0);

	--vector->size;

	spinlock_unlock(&vector->lock);
}

void vector_clear(struct vector *vector)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);

	vector->size = 0;

	spinlock_unlock(&vector->lock);
}

void *vector_get_element(struct vector *vector, size_t index)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);
	assert(index < vector->size);

	spinlock_unlock(&vector->lock);

	return vector_get_offset(vector, index);
}

static void vector_reallocate(struct vector *vector, size_t new_capacity)
{
	spinlock_lock(&vector->lock);

	assert(vector != NULL);
	assert(new_capacity != 0);

	if (new_capacity < vector->size)
	{
		vector->size = new_capacity;
	}

	void *new_data = kmalloc(new_capacity * vector->element_size);
	memcpy(new_data, vector->data, vector->size * vector->element_size);
	kfree(vector->data);

	vector->data = new_data;
	vector->capacity = new_capacity;

	spinlock_unlock(&vector->lock);
}

static void *vector_get_offset(struct vector *vector, size_t index)
{
	return vector->data + (index * vector->element_size);
}
