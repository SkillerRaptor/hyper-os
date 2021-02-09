#pragma once

namespace AK
{
	class Exception
	{
	private:
		const char* m_Message;

	public:
		Exception() noexcept;
		Exception(const Exception& other) noexcept;
		Exception(const char* message) noexcept;

		virtual const char* what() const noexcept;
	};
}