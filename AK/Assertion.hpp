#pragma once

#include <AK/Logger.hpp>

extern "C"
{
	__attribute__((noreturn)) inline void abort() { AK::Logger::error("ABORT!"); asm volatile("hlt"); }
	__attribute__((noreturn)) inline void _abort() { AK::Logger::error("ABORT!"); asm volatile("hlt"); }
}

#ifdef DEBUG
	#define VERIFY(expression) (static_cast<bool>(expr) ? void(0) : __assertion_failed(#    expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))
	#define VERIFY_NOT_REACHED() VERIFY(false)
#else
	#define VERIFY(expression)
	#define VERIFY_NOT_REACHED() _abort()
#endif
