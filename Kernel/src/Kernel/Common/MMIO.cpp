/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/MMIO.hpp>

namespace Kernel::MMIO
{
	void outb(uint8_t* address, uint8_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*address)
			: "r"(value)
			: "memory");
	}

	uint8_t inb(const uint8_t* address)
	{
		uint8_t return_value;

		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*address)
			: "memory");

		return return_value;
	}

	void outw(uint16_t* address, uint16_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*address)
			: "r"(value)
			: "memory");
	}

	uint16_t inw(const uint16_t* address)
	{
		uint16_t return_value;

		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*address)
			: "memory");

		return return_value;
	}

	void outd(uint32_t* address, uint32_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*address)
			: "r"(value)
			: "memory");
	}

	uint32_t ind(const uint32_t* address)
	{
		uint32_t return_value;

		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*address)
			: "memory");

		return return_value;
	}

	void outq(uint64_t* address, uint64_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*address)
			: "r"(value)
			: "memory");
	}

	uint64_t inq(const uint64_t* address)
	{
		uint64_t return_value;

		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*address)
			: "memory");

		return return_value;
	}
} // namespace Kernel::MMIO
