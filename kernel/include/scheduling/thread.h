/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "arch/registers.h"

#include <stddef.h>
#include <stdint.h>

typedef int16_t tid_t;

enum thread_state
{
	THREAD_STATE_IDLING,
	THREAD_STATE_RUNNING,
};

struct thread
{
	tid_t tid;
	enum thread_state state;

	uintptr_t kernel_stack;
	uintptr_t kernel_stack_size;

	struct registers registers;
};
