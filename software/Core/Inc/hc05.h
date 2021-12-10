/*
 * HC05.h
 *
 *  Created on: Nov 14, 2021
 *      Author: manuel
 */

#ifndef INC_HC05_H_
#define INC_HC05_H_

#include "cmsis_os.h"
#include "stm32f1xx_hal.h"

//---------- Buffers ----------------
#define LEN_BUFFER_RX LARGO_CLAVE
#define LEN_BUFFER_TX 32

//---------- Commands ---------------
#define CMD_CLAVE	'C'
#define CMD_RFID	'R'
#define CMD_MEM		'M'

//---------- Estados ----------------
#define ESPERANDO_INICIO	0
#define ESPERANDO_CLAVE		1
#define ESPERANDO_CMD		2
#define ESPERANDO_DATOS		3
#define ESPERANDO_FIN1		4
#define ESPERANDO_FIN2		5

//--------- funciones ----------------
void serieFreeRTOS_inicializar(UART_HandleTypeDef *huart, uint32_t len_colas);
void serieFreeRTOS_IRQ(void);
void serieFreeRTOS_putchar(uint8_t dato);
uint8_t serieFreeRTOS_getchar(void);


#endif /* INC_HC05_H_ */
