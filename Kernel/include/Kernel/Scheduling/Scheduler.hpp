/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Map.hpp>
#include <Kernel/Common/Registers.hpp>
#include <Kernel/Common/Types.hpp>
#include <Kernel/Scheduling/Task.hpp>
#include <Kernel/Synchronization/Spinlock.hpp>

namespace Kernel
{
	class Scheduler
	{
	public:
		static void initialize();
		
		static pid_t create_task(pid_t ppid, PageMap* page_map);
		static tid_t create_thread(pid_t pid, uint64_t rip, uint16_t cs);
		
		static void schedule(Registers* registers);
	
	private:
		static pid_t s_task_count;
		static tid_t s_thread_count;
		static Map<pid_t, Task> s_task_list;
		static Spinlock s_spinlock;
	};
	
	extern "C"
	{
		extern void switch_task(Registers* registers);
	}
} // namespace Kernel
