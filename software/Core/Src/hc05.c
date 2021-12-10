/*
 * HC05.c
 *
 *  Created on: Nov 14, 2021
 *      Author: manuel
 */

#include "own_drivers.h"



#define CHEQUEAR_SERIE_MS	(2)
static UART_HandleTypeDef *mi_uart;
static QueueHandle_t cola_tx;
static QueueHandle_t cola_rx;
static uint8_t enviando_serie;

uint8_t buffer_rx[LEN_BUFFER_RX];
uint8_t buffer_tx[LEN_BUFFER_TX];


static void TareaTxSerie(void *p)
{
	for(;;)
	{
		if(uxQueueMessagesWaiting(cola_tx)>0 && (enviando_serie == 0)) //Hay un dato esperando a ser enviado
		{
			enviando_serie = 1;
			__HAL_UART_ENABLE_IT(mi_uart, UART_IT_TXE);
		}
		vTaskDelay(CHEQUEAR_SERIE_MS);
	}
}

void serieFreeRTOS_IRQ(void)
{
	BaseType_t pxHigherPriorityTaskWoken;
	BaseType_t ret;
	uint8_t dato;
	if(__HAL_UART_GET_FLAG(mi_uart,UART_FLAG_RXNE))
	{
		dato = mi_uart->Instance->DR;
		xQueueSendFromISR(cola_rx,&dato, &pxHigherPriorityTaskWoken);
	}
	if(__HAL_UART_GET_FLAG(mi_uart,UART_FLAG_TXE))
	{

		ret = xQueueReceiveFromISR(cola_tx, &dato, &pxHigherPriorityTaskWoken);
		if(ret == pdTRUE)
		{
			mi_uart->Instance->DR = dato;
			enviando_serie = 1;
		}
		else
		{
			enviando_serie = 0;
			__HAL_UART_DISABLE_IT(mi_uart, UART_IT_TXE);
		}
	}
	portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);
}


void serieFreeRTOS_inicializar(UART_HandleTypeDef *huart, uint32_t len_colas)
{
	enviando_serie = 0;
	mi_uart = huart;
	cola_rx=xQueueCreate(len_colas,sizeof(uint8_t));	//Recibo de a un char
	cola_tx=xQueueCreate(len_colas,sizeof(uint8_t));
	if(xTaskCreate(TareaTxSerie,"serie",configMINIMAL_STACK_SIZE*3,NULL,3,NULL)!= pdPASS) Error_Handler();
	__HAL_UART_ENABLE_IT(mi_uart, UART_IT_RXNE);
}

void serieFreeRTOS_putchar(uint8_t dato)
{
	xQueueSend(cola_tx,&dato,0);
	HAL_Delay(1);
}

uint8_t serieFreeRTOS_getchar(void)
{
	uint8_t dato;
	xQueueReceive(cola_rx, &dato, portMAX_DELAY);
	return dato;
}


