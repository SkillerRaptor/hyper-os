/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

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
	uint8_t century;
};

void rtc_init(void);

uint8_t rtc_get_second(void);
uint8_t rtc_get_minute(void);
uint8_t rtc_get_hour(void);

uint8_t rtc_get_day(void);
uint8_t rtc_get_month(void);
uint16_t rtc_get_year(void);
uint8_t rtc_get_century(void);

struct time rtc_get_time(void);
struct date rtc_get_date(void);
