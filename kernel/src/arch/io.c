/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "arch/io.h"

uint8_t io_in8(uint16_t port)
{
	uint8_t return_value = 0;

	__asm__ __volatile__("inb %1, %0" : "=a"(return_value) : "Nd"(port));

	return return_value;
}

void io_out8(uint16_t port, uint8_t value)
{
	__asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint16_t io_in16(uint16_t port)
{
	uint16_t return_value = 0;

	__asm__ __volatile__("inw %1, %0" : "=a"(return_value) : "Nd"(port));

	return return_value;
}

void io_out16(uint16_t port, uint16_t value)
{
	__asm__ __volatile__("outw %0, %1" : : "a"(value), "Nd"(port));
}

uint32_t io_in32(uint16_t port)
{
	uint32_t return_value = 0;

	__asm__ __volatile__("inl %1, %0" : "=a"(return_value) : "Nd"(port));

	return return_value;
}

void io_out32(uint16_t port, uint32_t value)
{
	__asm__ __volatile__("outl %0, %1" : : "a"(value), "Nd"(port));
}

void io_wait(void)
{
	io_out8(0x80, 0x00);
}
