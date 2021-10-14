/*
 * sensor.c
 *
 *  Created on: Oct 6, 2021
 *      Author: manuel
 */

#include "sensor.h"
#include "tareas.h"

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

void tarea_sensor(void *p){

	uint8_t estado=0;

	for(;;){


		switch(estado){
		case 0:				//APAGADO
			xSemaphoreTake(sem_clave,portMAX_DELAY);
							if(clave_ok){
								estado=1;
								clave_ok = 0; //Bajo el flag
							}
			xSemaphoreGive(sem_clave);
			break;

		case 1:				//ENCENDIDO
			/*if(leer_sensor(1)){

			}
			if(leer_sensor(2)){

			}*/
			xSemaphoreTake(sem_clave,portMAX_DELAY);
							if(clave_ok){
								estado=0;
								clave_ok = 0; //Bajo el flag
							}
			xSemaphoreGive(sem_clave);
			break;

		}
		vTaskDelay(DEMORA_SENSOR / portTICK_RATE_MS);
	}
}
