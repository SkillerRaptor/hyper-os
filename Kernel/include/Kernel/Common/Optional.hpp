/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Utilities.hpp>

namespace Kernel
{
	template <typename T>
	class Optional
	{
	public:
		constexpr Optional() noexcept = default;

		constexpr Optional(T&& value)
			: m_value(Utilities::move(value))
			, m_has_value(true)
		{
		}

		constexpr T& value() &
		{
			return m_value;
		}

		constexpr const T& value() const&
		{
			return m_value;
		}

		constexpr T&& value() &&
		{
			return move(m_value);
		}

		constexpr const T&& value() const&&
		{
			return move(m_value);
		}

		template <class U>
		constexpr T value_or(U&& default_value)
		{
			if (!m_has_value)
			{
				return static_cast<T>(forward<U>(default_value));
			}

			return move(m_value);
		}

		template <class U>
		constexpr T value_or(U&& default_value) const
		{
			if (!m_has_value)
			{
				return static_cast<T>(forward<U>(default_value));
			}

			return m_value;
		}

		constexpr void reset() noexcept
		{
			if (!m_has_value)
			{
				return;
			}

			m_value.~T();
			m_has_value = false;
		}

	private:
		T m_value{};
		bool m_has_value{ false };
	};
} // namespace Kernel
