/*
 * adc.c
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */
#include "own_drivers.h"

/* ========= Variables Globales ==============*/
uint32_t ticks_adc;
//extern uint16_t raw_data[LEN_MUESTRAS*N_CANALES];

extern uint16_t datos_adc_1[N_SAMPLES];
extern uint16_t datos_adc_2[N_SAMPLES];
extern uint16_t *datos_adc_dma, *datos_adc_uso;

/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_DMA;
/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
static ADC_HandleTypeDef* adc;
/* ===========================================*/


void inic_punteros(void)
{
	memset(datos_adc_1,0,sizeof(datos_adc_1));
	memset(datos_adc_2,0,sizeof(datos_adc_2));
	datos_adc_dma = datos_adc_1;
	datos_adc_uso = datos_adc_2;
}

void adc_init(ADC_HandleTypeDef* handler)
{
	adc = handler;
	HAL_ADCEx_Calibration_Start(adc);
	HAL_Delay(100);
	inic_punteros();
	ticks_adc = HAL_GetTick();
}


void cambiar_punteros(void)
{
	if(datos_adc_dma == datos_adc_1)
	{
		datos_adc_dma = datos_adc_2;
		datos_adc_uso = datos_adc_1;
	}
	else
	{
		datos_adc_dma = datos_adc_1;
		datos_adc_uso = datos_adc_2;
	}
}


void tarea_conversiones(void *p)
{
	while(1)
	{
		HAL_ADC_Start_DMA(adc, (uint32_t*)datos_adc_dma, N_SAMPLES);
		vTaskDelay(TS_MS);
	}
}

void tarea_promedia(void *p)
{
	ejes joystick;
	while (1)
	{
		if (xSemaphoreTake(sem_DMA,portMAX_DELAY) == pdTRUE)
		{
			uint32_t i, x, y;
			x = y = 0;
			for (i = 0; i < N_SAMPLES / 2; i++)
			{
				x += datos_adc_uso[i * 2 + 1];
				y += datos_adc_uso[i * 2 + 0];
			}
			x /= N_SAMPLES / 2;
			y /= N_SAMPLES / 2;
			joystick.x = x;
			joystick.y = y;
		}
	}
}

//void update_adc()
//{
//	uint32_t i, promedio_ch0, promedio_ch1;
//	HAL_StatusTypeDef a;
//	uint8_t status = pdFALSE;
//
//	xSemaphoreGive(sem_DMA);	// Por las dudas de que se haya colgado
//
//	if((HAL_GetTick()-ticks_adc)>=TIC_MUESTRAS_MS)
//	{
//		ticks_adc = HAL_GetTick();
//
//		xSemaphoreTake(sem_DMA, portMAX_DELAY);
//		a = HAL_ADC_Start_DMA(adc, (uint32_t*)raw_data, LEN_MUESTRAS*N_CANALES);
//
//		status = xSemaphoreTake(sem_DMA, portMAX_DELAY);
//		if(status ==pdTRUE)
//		{
//			promedio_ch0=0;
//			promedio_ch1=0;
//			for(i=0;i<LEN_MUESTRAS;i++)
//			{
//				promedio_ch0+=raw_data[(i<<1)|0];
//				promedio_ch1+=raw_data[(i<<1)|1];
//			}
//			promedio_ch0/=LEN_MUESTRAS;
//			promedio_ch1/=LEN_MUESTRAS;
//			xSemaphoreGive(sem_DMA);
//
//		}
//	}
//
//}


