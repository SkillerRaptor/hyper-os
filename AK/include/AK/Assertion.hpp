#pragma once

extern "C"
{
	__attribute__((noreturn)) void abort() {}
	__attribute__((noreturn)) void _abort() {}
}

#ifdef DEBUG
	#define VERIFY(expression) (static_cast<bool>(expr) ? void(0) : __assertion_failed(#    expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))
	#define VERIFY_NOT_REACHED() VERIFY(false)
#else
	#define VERIFY(expression)
	#define VERIFY_NOT_REACHED() _abort()
#endif
