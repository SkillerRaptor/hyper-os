/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

void apic_init(void);

void lapic_send_eoi(void);

uint8_t lapic_get_current_cpu();

