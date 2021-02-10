#pragma once

#define __HyperOS_libc 1

#define _POSIX_VERSION 200809L

#define ALWAYS_INLINE inline __attribute__ ((always_inline))
#define __NORETURN __attribute__ ((noreturn))
#define __MALLOC __attribute__ ((malloc))
#define __PACKED __attribute__ ((packed))
#define PACKED [[gnu::packed]]

#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#undef __P
#define __P(a) a