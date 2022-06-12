/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <limine.h>

struct limine_hhdm_response *boot_get_hhdm();
struct limine_memmap_response *boot_get_memory_map();
struct limine_module_response *boot_get_modules();
struct limine_rsdp_response *boot_get_rsdp();
struct limine_smp_response *boot_get_smp();
struct limine_terminal_response *boot_get_terminal();
