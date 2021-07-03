/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/MMIO.hpp>

namespace Kernel
{
	void MMIO::outb(void* address, uint8_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*reinterpret_cast<uint8_t*>(address))
			: "r"(value)
			: "memory"
		);
	}
	
	uint8_t MMIO::inb(void* address)
	{
		uint8_t return_value = 0;
		
		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*reinterpret_cast<uint8_t*>(address))
			: "memory"
		);
		
		return return_value;
	}
	
	void MMIO::outw(void* address, uint16_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*reinterpret_cast<uint16_t*>(address))
			: "r"(value)
			: "memory"
		);
	}
	
	uint16_t MMIO::inw(void* address)
	{
		uint8_t return_value = 0;
		
		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*reinterpret_cast<uint16_t*>(address))
			: "memory"
		);
		
		return return_value;
	}
	
	void MMIO::outd(void* address, uint32_t value)
	{
		__asm__ __volatile__(
			"mov %0, %1"
			: "=m"(*reinterpret_cast<uint32_t*>(address))
			: "r"(value)
			: "memory"
		);
	}
	
	uint32_t MMIO::ind(void* address)
	{
		uint8_t return_value = 0;
		
		__asm__ __volatile__(
			"mov %0, %1"
			: "=r"(return_value)
			: "m"(*reinterpret_cast<uint32_t*>(address))
			: "memory"
		);
		
		return return_value;
	}
}
