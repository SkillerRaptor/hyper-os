/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#define KERNEL_CODE_SELECTOR 0x28
#define KERNEL_DATA_SELECTOR 0x30

struct tss
{
	uint32_t reserved_1;
	uint64_t rsp[3];
	uint64_t reserved_2;
	uint64_t ist[7];
	uint64_t reserved_3;
	uint16_t reserved_4;
	uint16_t io_offset;
} __attribute__((packed));

void gdt_init(void);
void gdt_load(void);

void gdt_load_tss(struct tss *tss);
