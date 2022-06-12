/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "arch/gdt.h"
#include "memory/vmm.h"
#include "scheduling/task.h"
#include "scheduling/thread.h"

#include <stdint.h>

struct cpu_info
{
	uint64_t id;
	uint32_t lapic_id;

	pid_t pid;
	tid_t tid;

	struct tss tss;
	struct page_map *page_map;
};

void cpu_write_msr(uint32_t msr, uint64_t value);
uint64_t cpu_read_msr(uint32_t msr);

uint64_t cpu_get_local_id();
struct cpu_info *cpu_get_local_info();

void cpu_set_kernel_gs(uintptr_t address);
