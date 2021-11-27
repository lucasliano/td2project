/*
 * sensor.c
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */


#include "main.h"

extern xSemaphoreHandle sem_clave;
extern uint8_t clave_ok;

uint8_t leer_sensor(uint8_t sensor){
	if (sensor == 1){
		return HAL_GPIO_ReadPin(PUERTO_SENSOR1,PIN_SENSOR1);
	}
	else if(sensor == 2){
		return HAL_GPIO_ReadPin(PUERTO_SENSOR2,PIN_SENSOR2);
	}
	else
		return 2; //error
}
