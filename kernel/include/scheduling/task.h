/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "lib/vector.h"
#include "memory/vmm.h"
#include "scheduling/thread.h"

#include <stddef.h>
#include <stdint.h>

typedef int16_t pid_t;

enum task_state
{
	TASK_STATE_IDLING,
	TASK_STATE_RUNNING,
};

struct thread_index
{
	tid_t tid;
	size_t index;
};

struct task
{
	pid_t pid;
	tid_t tid;
	enum task_state state;

	struct page_map *page_map;
};
