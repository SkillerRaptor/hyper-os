#include <AK/StringBuilder.h>

#include <AK/Utility.h>

namespace AK
{
	void StringBuilder::append(String& string)
	{
		m_Strings.push_back(string);
	}

	void StringBuilder::append(const String& string)
	{
		m_Strings.push_back(string);
	}

	void StringBuilder::append(const char string)
	{
		m_Strings.push_back(String(string));
	}

	void StringBuilder::append(const char* string)
	{
		m_Strings.push_back(String(string));
	}

	void StringBuilder::clear()
	{
		m_Strings.clear();
	}

	String StringBuilder::build()
	{
		String r;
		for (size_t i = 0; i < m_Strings.size(); i++)
		{
			String s = m_Strings[i];
			r = r + s;
		}
		return r;
	}
}