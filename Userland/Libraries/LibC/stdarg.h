#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

using va_list = __builtin_va_list;

#define va_start(ap, v) __builtin_va_start(ap, v)
#define va_arg(ap, t) __builtin_va_arg(ap, t)
#define va_end(ap) __builtin_va_end(ap)

__END_DECLS