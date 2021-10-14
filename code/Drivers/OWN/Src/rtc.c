/*
 * rtc.c
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#include "rtc.h"

extern RTC_HandleTypeDef hrtc;


uint8_t obtener_tiempo(uint8_t dato){
	RTC_TimeTypeDef tiempo={0};

	HAL_RTC_GetTime(&hrtc,&tiempo,RTC_FORMAT_BIN);

	if(dato == HORA)
		return tiempo.Hours;
	else if (dato == MINUTOS)
		return tiempo.Minutes;
	else
		return 0xFF;


}
