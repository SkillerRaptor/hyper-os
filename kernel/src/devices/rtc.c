/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "devices/rtc.h"

#include "arch/fadt.h"
#include "arch/io.h"
#include "lib/logger.h"

#include <stdbool.h>

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

static bool rtc_is_leap_year(uint16_t year);
static uint16_t rtc_get_days_of_year(uint16_t year);
static uint16_t rtc_get_days_since_epoch(uint16_t year);
static uint16_t rtc_get_day_of_year(uint16_t year, uint8_t month, uint8_t day);

static uint8_t rtc_get_second(void);
static uint8_t rtc_get_minute(void);
static uint8_t rtc_get_hour(void);
static uint8_t rtc_get_day(void);
static uint8_t rtc_get_month(void);
static uint16_t rtc_get_year(void);

static time_t s_boot_time = 0;

void rtc_init(void)
{
	s_boot_time = rtc_now();
	logger_info("RTC: Initialized");
}

time_t rtc_now()
{
	const struct date date = rtc_get_date();
	const struct time time = rtc_get_time();
	const time_t days_since_epoch =
		rtc_get_days_since_epoch(date.year) +
		rtc_get_day_of_year(date.year, date.month, date.day);
	return ((days_since_epoch * 24 + time.hour) * 60 + time.minute) * 60 +
				 time.second;
}

struct time rtc_get_time(void)
{
	struct time time = { 0 };
	time.second = rtc_get_second();
	time.minute = rtc_get_minute();
	time.hour = rtc_get_hour();

	return time;
}

struct date rtc_get_date(void)
{
	struct date date = { 0 };
	date.day = rtc_get_day();
	date.month = rtc_get_month();
	date.year = rtc_get_year();

	return date;
}

time_t rtc_get_boot_time()
{
	return s_boot_time;
}

static bool rtc_is_updating(void)
{
	io_out8(CMOS_ADDRESS, 0x0a);
	return (io_in8(CMOS_DATA) & 0x80);
}

static uint8_t rtc_read_register(uint8_t rtc_register)
{
	while (rtc_is_updating())
	{
		// NOTE: Prevents compiler from optimizing loop
		__asm__ __volatile__("");
	}

	io_out8(CMOS_ADDRESS, rtc_register);
	return io_in8(CMOS_DATA);
}

static bool rtc_is_leap_year(uint16_t year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static uint16_t rtc_get_days_of_year(uint16_t year)
{
	return 365 + (rtc_is_leap_year(year) ? 1 : 0);
}

static uint16_t rtc_get_days_since_epoch(uint16_t year)
{
	uint16_t days = 0;
	for (int current_year = 1970; current_year < year; ++current_year)
	{
		days += rtc_get_days_of_year(current_year);
	}

	for (int current_year = year; current_year < 1970; ++current_year)
	{
		days -= rtc_get_days_of_year(current_year);
	}

	return days;
}

static uint16_t rtc_get_day_of_year(uint16_t year, uint8_t month, uint8_t day)
{
	uint16_t day_from_year = day - 1;
	switch (month)
	{
	case 1:
		day_from_year += 0;
		break;
	case 2:
		day_from_year += 31;
		break;
	case 3:
		day_from_year += 59;
		break;
	case 4:
		day_from_year += 90;
		break;
	case 5:
		day_from_year += 120;
		break;
	case 6:
		day_from_year += 151;
		break;
	case 7:
		day_from_year += 181;
		break;
	case 8:
		day_from_year += 212;
		break;
	case 9:
		day_from_year += 243;
		break;
	case 10:
		day_from_year += 273;
		break;
	case 11:
		day_from_year += 304;
		break;
	case 12:
		day_from_year += 334;
		break;
	}

	if (rtc_is_leap_year(year) && month >= 3)
	{
		++day_from_year;
	}

	return day_from_year;
}

static uint8_t rtc_get_second(void)
{
	const uint8_t seconds = rtc_read_register(0x00);
	const uint8_t second = (seconds & 0x0f) + ((seconds / 16) * 10);
	return second;
}

static uint8_t rtc_get_minute(void)
{
	const uint8_t minutes = rtc_read_register(0x02);
	const uint8_t minute = (minutes & 0x0f) + ((minutes / 16) * 10);
	return minute;
}

static uint8_t rtc_get_hour(void)
{
	const uint8_t hours = rtc_read_register(0x04);
	const uint8_t hour =
		((hours & 0x0f) + (((hours & 0x70) / 16) * 10)) | (hours & 0x80);
	return hour;
}

static uint8_t rtc_get_day(void)
{
	const uint8_t days = rtc_read_register(0x07);
	const uint8_t day = (days & 0x0f) + ((days / 16) * 10);
	return day;
}

static uint8_t rtc_get_month(void)
{
	const uint8_t months = rtc_read_register(0x08);
	const uint8_t month = (months & 0x0f) + ((months / 16) * 10);
	return month;
}

static uint16_t rtc_get_year(void)
{
	const uint8_t years = rtc_read_register(0x09);
	const uint8_t year = (years & 0x0f) + ((years / 16) * 10);
	return year + 2000;
}
