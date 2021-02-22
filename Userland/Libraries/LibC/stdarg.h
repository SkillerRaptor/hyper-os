#ifndef HYPEROS_USERLAND_LIBRARIES_LIBC_STDARG_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBC_STDARG_H_

#include <sys/cdefs.h>

typedef __builtin_va_list va_list;

#define va_start(ap, v) __builtin_va_start(ap, v)
#define va_arg(ap, t) __builtin_va_arg(ap, t)
#define va_end(ap) __builtin_va_end(ap)

#endif