#pragma once

#include <AK/TypeTraits.hpp>

namespace AK
{
	template<class T>
	inline T&& forward(typename RemoveReference<T>::type& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template<class T>
	inline T&& forward(typename RemoveReference<T>::type&& t) noexcept
	{
		return static_cast<T&&>(t);
	}
	
	template<class T>
	inline typename RemoveReference<T>::type&& move(T&& t) noexcept
	{
		return static_cast<typename RemoveReference<T>::type&&>(t);
	}
}
