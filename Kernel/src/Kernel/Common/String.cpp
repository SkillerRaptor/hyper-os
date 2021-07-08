/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/String.hpp>

namespace Kernel
{
	String::String(const char* string)
		: m_size(strlen(string))
		, m_buffer(new char[m_size])
	{
	}
} // namespace Kernel
