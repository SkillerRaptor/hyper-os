/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "scheduling/smp.h"

#include "arch/apic.h"
#include "arch/boot.h"
#include "arch/cpu.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "lib/assert.h"
#include "lib/logger.h"
#include "lib/memory.h"
#include "memory/kmalloc.h"
#include "memory/pmm.h"
#include "memory/vmm.h"
#include "scheduling/scheduler.h"
#include "scheduling/spinlock.h"

#include <stddef.h>

static uint64_t s_online_cpu_count = 0;
static uint32_t s_bsp_lapic_id = 0;
static struct cpu_info *s_cpu_infos = NULL;
static struct spinlock s_lock = { 0 };

static void cpu_init(struct limine_smp_info *smp_info);

void smp_init(void)
{
	struct limine_smp_response *smp_response = boot_get_smp();
	assert(smp_response != NULL);

	s_bsp_lapic_id = smp_response->bsp_lapic_id;
	s_cpu_infos = kmalloc(sizeof(struct cpu_info) * smp_response->cpu_count);

	logger_info("SMP: %u available CPUs were found", smp_response->cpu_count);

	struct limine_smp_info **cpus = smp_response->cpus;
	for (size_t i = 0; i < smp_response->cpu_count; ++i)
	{
		const uint64_t stack =
			(uintptr_t) pmm_calloc(1) + PAGE_SIZE + pmm_get_memory_offset();

		s_cpu_infos[i].id = i;
		s_cpu_infos[i].lapic_id = cpus[i]->lapic_id;
		s_cpu_infos[i].pid = -1;
		s_cpu_infos[i].tid = -1;
		s_cpu_infos[i].tss.rsp[0] = stack;
		s_cpu_infos[i].page_map = vmm_get_kernel_page_map();

		cpus[i]->extra_argument = (uint64_t) &s_cpu_infos[i];

		if (cpus[i]->lapic_id == s_bsp_lapic_id)
		{
			cpu_init(cpus[i]);
			continue;
		}

		cpus[i]->goto_address = cpu_init;
	}

	while (s_online_cpu_count != smp_response->cpu_count)
	{
		// NOTE: Prevents compiler from optimizing loop
		__asm__ __volatile__("");
	}

	logger_info("SMP: %u CPUs now online", s_online_cpu_count);

	logger_info("SMP: Initialized");
}

static void cpu_init(struct limine_smp_info *smp_info)
{
	gdt_load();
	idt_load();
	vmm_switch_page_map(vmm_get_kernel_page_map());

	cpu_set_kernel_gs((uintptr_t) smp_info->extra_argument);

	struct cpu_info *cpu_info = cpu_get_local_info();

	gdt_load_tss(&cpu_info->tss);

	lapic_enable();

	spinlock_lock(&s_lock);
	++s_online_cpu_count;
	spinlock_unlock(&s_lock);

	if (cpu_info->lapic_id == s_bsp_lapic_id)
	{
		return;
	}

	scheduler_wait();
}

struct cpu_info *smp_get_cpu_infos()
{
	return s_cpu_infos;
}
