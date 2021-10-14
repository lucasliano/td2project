/*
 * sensor.h
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define PUERTO_SENSOR1	GPIOA
#define PIN_SENSOR1		GPIO_PIN_9

#define PUERTO_SENSOR2	GPIOA
#define PIN_SENSOR2		GPIO_PIN_8

#define DEMORA_SENSOR	300 //ms

uint8_t leer_sensor(uint8_t);
void tarea_sensor(void *p);

#endif /* INC_SENSOR_H_ */
