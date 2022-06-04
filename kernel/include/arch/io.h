/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

uint8_t io_in8(uint16_t port);
void io_out8(uint16_t port, uint8_t value);

uint16_t io_in16(uint16_t port);
void io_out16(uint16_t port, uint16_t value);

uint32_t io_in32(uint16_t port);
void io_out32(uint16_t port, uint32_t value);

void io_wait(void);
