/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stddef.h>

typedef void (*interrupt_handler)(size_t);

void idt_init(void);
void idt_load(void);

void idt_set_handler(size_t interrupt, interrupt_handler handler);

