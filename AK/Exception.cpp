#include <AK/Exception.h>

namespace AK
{
	Exception::Exception() noexcept
		: m_Message("")
	{
	}

	Exception::Exception(const Exception& other) noexcept
		: m_Message(other.m_Message)
	{
	}
	
	Exception::Exception(const char* message) noexcept
		: m_Message(message)
	{
	}

	const char* Exception::what() const noexcept
	{
		return m_Message;
	}
}
