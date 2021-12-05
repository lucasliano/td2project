/*
 * rtc.c
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#include "main.h"

extern RTC_HandleTypeDef hrtc;


RTC_TimeTypeDef obtener_tiempo(void){
	RTC_TimeTypeDef tiempo={0};

	HAL_RTC_GetTime(&hrtc,&tiempo,RTC_FORMAT_BIN);

	return tiempo;
}
