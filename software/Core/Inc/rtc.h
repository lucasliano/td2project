/*
 * rtc.h
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"

#define HORA 0
#define MINUTOS 1

RTC_TimeTypeDef obtener_tiempo(void);
void rtc_init(void);
void rtc_update(RTC_TimeTypeDef);
uint8_t string_to_int(uint8_t *p);


#endif /* INC_RTC_H_ */
