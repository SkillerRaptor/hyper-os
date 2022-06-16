/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "scheduling/scheduler.h"

#include "arch/apic.h"
#include "arch/cpu.h"
#include "arch/idt.h"
#include "lib/logger.h"
#include "lib/memory.h"
#include "lib/vector.h"
#include "memory/pmm.h"
#include "memory/vmm.h"
#include "scheduling/spinlock.h"

#include <stddef.h>

static struct vector s_task_queue = { 0 };
static struct vector s_task_list = { 0 };
static struct vector s_thread_list = { 0 };
static int64_t s_task_count = 0;
static int64_t s_thread_count = 0;
static pid_t s_kernel_process_id = 0;
static struct spinlock s_lock = { 0 };

static void scheduler_schedule(struct registers *);

extern void switch_task(struct registers *registers);

void scheduler_init(void)
{
	idt_set_handler(LAPIC_TIMER_ISR, scheduler_schedule);
	logger_info(
		"Scheduler: LAPIC timer ISR registered at 0x%02x", LAPIC_TIMER_ISR);

	vector_init(&s_task_queue, sizeof(pid_t));
	vector_init(&s_task_list, sizeof(struct task));
	vector_init(&s_thread_list, sizeof(struct thread));

	s_kernel_process_id = scheduler_create_task(vmm_get_kernel_page_map());
	logger_info("Scheduler: Kernel process created with pid %u", s_kernel_process_id);

	logger_info("Scheduler: Initialized");
}

__attribute__((noreturn)) void scheduler_wait(void)
{
	__asm__ __volatile__("sti");

	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}

pid_t scheduler_create_task(struct page_map *page_map)
{
	struct task task = { 0 };
	task.pid = s_task_count++;
	task.state = TASK_STATE_IDLING;
	task.page_map = page_map != NULL ? page_map : vmm_create_page_map();

	vector_push_back(&s_task_queue, &task.pid);
	vector_push_back(&s_task_list, &task);

	return task.pid;
}

tid_t scheduler_create_thread(pid_t pid, uintptr_t rip, uint16_t cs)
{
	if (pid == -1)
	{
		return -1;
	}

	struct task *task = vector_get_element(&s_task_list, pid);
	if (task->pid == -1)
	{
		return -1;
	}

	const uintptr_t stack = (uintptr_t) pmm_calloc(1) + PAGE_SIZE;

	struct thread thread = { 0 };
	thread.tid = s_thread_count++;
	thread.state = THREAD_STATE_IDLING;
	thread.kernel_stack = stack;
	thread.kernel_stack_size = PAGE_SIZE;
	thread.registers.rip = rip;
	thread.registers.rsp = thread.kernel_stack + pmm_get_memory_offset();
	thread.registers.cs = cs;
	thread.registers.ss = cs + 8;

	task->tid = thread.tid;

	vector_push_back(&s_thread_list, &thread);

	return thread.tid;
}

pid_t scheduler_get_kernel_process()
{
	return s_kernel_process_id;
}

static void scheduler_schedule(struct registers *registers)
{
	spinlock_lock(&s_lock);

	pid_t next_pid = -1;
	if (s_task_queue.size != 0)
	{
		next_pid = *((pid_t *) vector_get_element(&s_task_queue, 0));
	}

	struct cpu_info *cpu_info = cpu_get_local_info();
	if (next_pid == -1)
	{
		if (cpu_info->pid == -1)
		{
			spinlock_unlock(&s_lock);
			return;
		}

		next_pid = cpu_info->pid;
	}

	if (s_task_list.size == 0)
	{
		spinlock_unlock(&s_lock);
		return;
	}

	struct task *next_task = vector_get_element(&s_task_list, next_pid);
	if (next_task->state == TASK_STATE_RUNNING)
	{
		spinlock_unlock(&s_lock);
		return;
	}

	if (next_task->tid == -1)
	{
		spinlock_unlock(&s_lock);
		return;
	}

	if (s_thread_list.size == 0)
	{
		spinlock_unlock(&s_lock);
		return;
	}

	struct thread *next_thread =
		vector_get_element(&s_thread_list, next_task->tid);
	if (next_thread->state == THREAD_STATE_RUNNING)
	{
		spinlock_unlock(&s_lock);
		return;
	}

	if (cpu_info->pid != -1 && cpu_info->tid != -1)
	{
		struct task *last_task = vector_get_element(&s_task_list, cpu_info->pid);
		struct thread *last_thread =
			vector_get_element(&s_thread_list, cpu_info->tid);

		last_task->state = TASK_STATE_IDLING;
		last_thread->state = THREAD_STATE_IDLING;

		vector_push_back(&s_task_queue, &last_task->pid);

		last_thread->registers = *registers;
	}

	cpu_info->pid = next_pid;
	cpu_info->tid = next_thread->tid;
	cpu_info->page_map = next_task->page_map;

	vmm_switch_page_map(cpu_info->page_map);

	next_task->state = TASK_STATE_RUNNING;
	next_thread->state = THREAD_STATE_RUNNING;

	vector_pop_front(&s_task_queue);

	lapic_send_eoi();

	spinlock_unlock(&s_lock);

	switch_task(&next_thread->registers);
}
