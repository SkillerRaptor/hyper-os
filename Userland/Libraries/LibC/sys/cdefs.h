#pragma once

#define ALWAYS_INLINE inline __attribute__ ((always_inline))
#define __NORETURN __attribute__ ((noreturn))
#define __MALLOC __attribute__ ((malloc))
#define __PACKED __attribute__ ((packed))

#undef __P
#define __P(a) a
