/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

typedef int64_t time_t;

struct time
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
};

struct date
{
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

void rtc_init(void);

time_t rtc_now();
struct time rtc_get_time(void);
struct date rtc_get_date(void);

time_t rtc_get_boot_time();
