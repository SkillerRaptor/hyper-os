/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define KERNEL_CODE_SELECTOR 0x28
#define KERNEL_DATA_SELECTOR 0x30

void gdt_init();
void gdt_load();
