/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

void pic_remap(void);
void pic_disable(void);

void pic_set_interrupt_request_mask(uint8_t interrupt_request_line);
void pic_clear_interrupt_request_mask(uint8_t interrupt_request_line);
