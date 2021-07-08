/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

namespace Kernel
{
	using ssize_t = int64_t;
	
	using pid_t = ssize_t;
	using tid_t = ssize_t;
}
