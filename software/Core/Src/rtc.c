/*
 * rtc.c
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#include "main.h"

extern RTC_HandleTypeDef hrtc;

void rtc_init(void)
{
	RTC_TimeTypeDef tiempo;
	tiempo.Hours = 0;
	tiempo.Minutes = 0;
	tiempo.Seconds = 0;

	HAL_RTC_SetTime(&hrtc, &tiempo, RTC_FORMAT_BIN);
}

void rtc_update(RTC_TimeTypeDef tiempo)
{
	HAL_RTC_SetTime(&hrtc, &tiempo, RTC_FORMAT_BIN);
}

RTC_TimeTypeDef obtener_tiempo(void){
	RTC_TimeTypeDef tiempo={0};

	HAL_RTC_GetTime(&hrtc,&tiempo,RTC_FORMAT_BIN);

	return tiempo;
}
