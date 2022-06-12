/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#define LAPIC_TIMER_ISR 0x20

void apic_init(void);

void lapic_send_eoi(void);

uint8_t lapic_get_current_cpu();

