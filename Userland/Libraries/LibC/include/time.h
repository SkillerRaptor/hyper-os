/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPEROS_LIBC_TIME_H_
#define HYPEROS_LIBC_TIME_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef unsigned int time_t;

struct timeval
{
	time_t tv_sec;
	long tv_usec;
};

typedef struct timeval timeval_t;

struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};

typedef struct timeval timeval_t;

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

time_t time(time_t* time);

__END_DECLS

#endif // HYPEROS_LIBC_TIME_H_
