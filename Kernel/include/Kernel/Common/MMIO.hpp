/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel::MMIO
{
	void outb(uint8_t* address, uint8_t value);
	uint8_t inb(const uint8_t* address);

	void outw(uint16_t* address, uint16_t value);
	uint16_t inw(const uint16_t* address);

	void outd(uint32_t* address, uint32_t value);
	uint32_t ind(const uint32_t* address);

	void outq(uint64_t* address, uint64_t value);
	uint64_t inq(const uint64_t* address);
} // namespace Kernel::MMIO
