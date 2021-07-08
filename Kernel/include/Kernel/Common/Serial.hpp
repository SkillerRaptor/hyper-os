/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace Kernel::Serial
{
	void initialize();

	void write(char character);
	void write(const char* string);
} // namespace Kernel::Serial
