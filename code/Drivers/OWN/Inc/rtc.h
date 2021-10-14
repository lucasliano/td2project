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

uint8_t obtener_tiempo(uint8_t);


#endif /* INC_RTC_H_ */
