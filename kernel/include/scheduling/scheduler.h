/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "memory/vmm.h"
#include "scheduling/task.h"
#include "scheduling/thread.h"

#include <stdint.h>

void scheduler_init(void);

__attribute__((noreturn)) void scheduler_wait(void);

pid_t scheduler_create_task(struct page_map *page_map);
tid_t scheduler_create_thread(pid_t pid, uintptr_t rip, uint16_t cs);

pid_t scheduler_get_kernel_process();
