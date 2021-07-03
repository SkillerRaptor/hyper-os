/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_STDINT_H_
#define HYPEROS_LIBC_STDINT_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long int int64_t;
typedef unsigned long int uint64_t;

typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int int_least16_t;
typedef unsigned short int uint_least16_t;
typedef int int_least32_t;
typedef unsigned int uint_least32_t;
typedef long int int_least64_t;
typedef unsigned long int uint_least64_t;

typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef long int int_fast16_t;
typedef unsigned long int uint_fast16_t;
typedef long int int_fast32_t;
typedef unsigned long int uint_fast32_t;
typedef long int int_fast64_t;
typedef unsigned long int uint_fast64_t;

typedef long int intmax_t;
typedef unsigned long int uintmax_t;

__END_DECLS

#endif // HYPEROS_LIBC_STDINT_H_
