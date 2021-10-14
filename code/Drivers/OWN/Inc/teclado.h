/*
 * teclado.h
 *
 *  Created on: Sep 20, 2021
 *      Author: manuel
 */

#ifndef INC_TECLADO_H_
#define INC_TECLADO_H_

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define PUERTO_COLUMNA123  GPIOB
#define PUERTO_COLUMNA4  GPIOA
#define COLUMNA1		GPIO_PIN_5
#define COLUMNA2		GPIO_PIN_4
#define COLUMNA3		GPIO_PIN_3
#define COLUMNA4		GPIO_PIN_10

#define PUERTO_FILA  	GPIOA
#define FILA1			GPIO_PIN_2
#define FILA2			GPIO_PIN_3
#define FILA3			GPIO_PIN_5
#define FILA4			GPIO_PIN_6

#define DEMORA_REBOTE	20 //ms
#define DEMORA_LECTURA	20 //ms

#define LARGO_CLAVE 4
#define CLAVE1 '8'
#define CLAVE2 '4'
#define CLAVE3 '3'
#define CLAVE4 '7'

void tarea_teclado(void *p);
uint8_t chequear_clave(uint8_t *t);
void init_teclado();


#endif /* INC_TECLADO_H_ */
