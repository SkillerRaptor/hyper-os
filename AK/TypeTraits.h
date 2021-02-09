#pragma once

namespace AK
{
	template<class T>
	struct remove_reference
	{
		typedef T type;
	};

	template<class T>
	struct remove_reference<T&>
	{
		typedef T type;
	};

	template<class T>
	struct remove_reference<T&&>
	{
		typedef T type;
	};
}