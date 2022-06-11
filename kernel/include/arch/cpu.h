/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

void cpu_write_msr(uint32_t msr, uint64_t value);
uint64_t cpu_read_msr(uint32_t msr);
