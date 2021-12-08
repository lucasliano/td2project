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

#define LEN_BUFFER_RX 8
#define LEN_BUFFER_TX 8

void bt_inicializar(UART_HandleTypeDef *huart);
void bt_tx(uint8_t *datos, uint32_t len);
void bt_rx(uint8_t *datos, uint32_t len);
void tarea_rx(void *p);
void tarea_tx(void *p);

#include "main.h"
void serieFreeRTOS_inicializar(UART_HandleTypeDef *huart, uint32_t len_colas);
void serieFreeRTOS_IRQ(void);
void serieFreeRTOS_putchar(uint8_t dato);
uint8_t serieFreeRTOS_getchar(void);


#endif /* INC_HC05_H_ */
