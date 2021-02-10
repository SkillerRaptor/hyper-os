#pragma once

#include <AK/TypeTraits.h>

template<class T>
inline T&& forward(typename remove_reference<T>::type& t) noexcept
{
	return static_cast<T&&>(t);
}

template<class T>
inline T&& forward(typename remove_reference<T>::type&& t) noexcept
{
	return static_cast<T&&>(t);
}

template<class T>
inline typename remove_reference<T>::type&& move(T&& t) noexcept
{
	return static_cast<typename remove_reference<T>::type&&>(t);
}