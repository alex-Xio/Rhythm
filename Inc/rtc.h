#ifndef RTC_H_
#define RTC_H_

#include "stm32f4xx.h"
void rtc_init();
void rtc_set_header();

uint8_t rtc_get_dt();
uint8_t rtc_get_du();
uint8_t rtc_get_mt();
uint8_t rtc_get_mu();

#endif // RTC_H_