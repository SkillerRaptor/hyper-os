/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDINT_H_
#define HYPEROS_LIBC_STDINT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

#if defined(__x86_64__)
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
#elif defined(__i386__)
typedef signed long long int __int64_t;
typedef unsigned long long int __uint64_t;
#endif

typedef __int8_t int8_t;
typedef __uint8_t uint8_t;
typedef __int16_t int16_t;
typedef __uint16_t uint16_t;
typedef __int32_t int32_t;
typedef __uint32_t uint32_t;
typedef __int64_t int64_t;
typedef __uint64_t uint64_t;

typedef signed char __int_least8_t;
typedef unsigned char __uint_least8_t;
typedef short int __int_least16_t;
typedef unsigned short int __uint_least16_t;
typedef int __int_least32_t;
typedef unsigned int __uint_least32_t;

#if defined(__x86_64__)
typedef long int __int_least64_t;
typedef unsigned long int __uint_least64_t;
#elif defined(__i386__)
typedef long long int __int_least64_t;
typedef unsigned long long int __uint_least64_t;
#endif

typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;

typedef signed char __int_fast8_t;
typedef unsigned char __uint_fast8_t;

#if defined(__x86_64__)
typedef long int __int_fast16_t;
typedef unsigned long int __uint_fast16_t;
typedef long int __int_fast32_t;
typedef unsigned long int __uint_fast32_t;
typedef long int __int_fast64_t;
typedef unsigned long int __uint_fast64_t;
#elif defined(__i386__)
typedef int __int_fast16_t;
typedef unsigned int __uint_fast16_t;
typedef int __int_fast32_t;
typedef unsigned int __uint_fast32_t;
typedef long long int __int_fast64_t;
typedef unsigned long long int __uint_fast64_t;
#endif

typedef __int_fast8_t int_fast8_t;
typedef __int_fast16_t int_fast16_t;
typedef __int_fast32_t int_fast32_t;
typedef __int_fast64_t int_fast64_t;
typedef __uint_fast8_t uint_fast8_t;
typedef __uint_fast16_t uint_fast16_t;
typedef __uint_fast32_t uint_fast32_t;
typedef __uint_fast64_t uint_fast64_t;

#if defined(__x86_64__)
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
#elif defined(__i386__)
typedef long long int __intmax_t;
typedef unsigned long long int __uintmax_t;
#endif

typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;

__END_DECLS

#endif // HYPEROS_LIBC_STDINT_H_
