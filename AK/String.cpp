/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <AK/Assertion.hpp>
#include <AK/String.hpp>

namespace AK
{
	String::Iterator String::begin() noexcept
	{
		return Iterator::begin(*this);
	}
	
	String::ConstIterator String::begin() const noexcept
	{
		return ConstIterator::begin(*this);
	}
	
	String::ConstIterator String::cbegin() const noexcept
	{
		return ConstIterator::begin(*this);
	}
	
	String::Iterator String::end() noexcept
	{
		return Iterator::end(*this);
	}
	
	String::ConstIterator String::end() const noexcept
	{
		return ConstIterator::end(*this);
	}
	
	String::ConstIterator String::cend() const noexcept
	{
		return ConstIterator::end(*this);
	}
	
	char& String::at(size_t position)
	{
		VERIFY(position < m_size);
		return m_buffer[position];
	}
	
	const char& String::at(size_t position) const
	{
		VERIFY(position < m_size);
		return m_buffer[position];
	}
	
	char& String::operator[](size_t position) noexcept
	{
		return m_buffer[position];
	}
	
	const char& String::operator[](size_t position) const noexcept
	{
		return m_buffer[position];
	}
	
	size_t String::length() const noexcept
	{
		return m_size;
	}
	
	size_t String::size() const noexcept
	{
		return m_size;
	}
	
	size_t String::max_size() const noexcept
	{
		return m_size;
	}
}
