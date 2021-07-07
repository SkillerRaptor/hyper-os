/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Map.hpp>
#include <Kernel/Common/Registers.hpp>
#include <Kernel/Common/Types.hpp>
#include <Kernel/Memory/VirtualMemoryManager.hpp>

namespace Kernel
{
	struct Thread;
	
	struct Task
	{
		enum class State
		{
			None,
			Waiting,
			Running
		};
		
		pid_t pid;
		pid_t ppid;
		State state;
		
		size_t idle_count;
		
		PageMap* page_map;
		Map<ssize_t, Thread> threads;
	};
	
	struct Thread
	{
		tid_t tid;
		Task::State state;
		
		size_t idle_count;
		ssize_t error;
		
		uintptr_t kernel_stack;
		uintptr_t kernel_stack_size;
		
		Registers registers;
	};
	
} // namespace Kernel
