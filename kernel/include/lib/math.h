/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define DIV_ROUND_UP(x, y) ((x + (y - 1)) / y)
#define ALIGN_UP(x, y) (DIV_ROUND_UP(x, y) * y)
#define ALIGN_DOWN(x, y) ((x / y) * y)
