/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/cpu.h"

void cpu_write_msr(uint32_t msr, uint64_t value)
{
	const uint32_t edx = value >> 32;
	const uint32_t eax = (uint32_t) value;
	__asm__ __volatile__("wrmsr" : : "a"(eax), "d"(edx), "c"(msr) : "memory");
}

uint64_t cpu_read_msr(uint32_t msr)
{
	uint32_t edx = 0;
	uint32_t eax = 0;
	__asm__ __volatile__("rdmsr" : "=a"(eax), "=d"(edx) : "c"(msr) : "memory");
	return ((uint64_t) edx << 32) | eax;
}
