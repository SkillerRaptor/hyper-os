#pragma once

namespace AK
{
	template<class T>
	struct RemoveReference
	{
		typedef T type;
	};
	
	template<class T>
	struct RemoveReference<T&>
	{
		typedef T type;
	};
	
	template<class T>
	struct RemoveReference<T&&>
	{
		typedef T type;
	};
}
