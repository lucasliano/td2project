/*
 * adc.c
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */
#include "own_drivers.h"

/* ========= Variables Globales ==============*/
uint32_t ticks_adc;
extern uint16_t raw_data[LEN_MUESTRAS*N_CANALES];
/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_DMA;
/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
static ADC_HandleTypeDef* adc;
/* ===========================================*/


void adc_init(ADC_HandleTypeDef* handler)
{
	adc = handler;
	HAL_ADCEx_Calibration_Start(adc);
	ticks_adc = HAL_GetTick();
}

void update_adc()
{
	uint32_t i, promedio_ch0, promedio_ch1;
	HAL_StatusTypeDef a;
	uint8_t status = pdFALSE;

	xSemaphoreGive(sem_DMA);	// Por las dudas de que se haya colgado

	if((HAL_GetTick()-ticks_adc)>=TIC_MUESTRAS_MS)
	{
		ticks_adc = HAL_GetTick();

		xSemaphoreTake(sem_DMA, portMAX_DELAY);
		a = HAL_ADC_Start_DMA(adc, (uint32_t*)raw_data, LEN_MUESTRAS*N_CANALES);

		status = xSemaphoreTake(sem_DMA, portMAX_DELAY);
		if(status ==pdTRUE)
		{
			promedio_ch0=0;
			promedio_ch1=0;
			for(i=0;i<LEN_MUESTRAS;i++)
			{
				promedio_ch0+=raw_data[(i<<1)|0];
				promedio_ch1+=raw_data[(i<<1)|1];
			}
			promedio_ch0/=LEN_MUESTRAS;
			promedio_ch1/=LEN_MUESTRAS;
			xSemaphoreGive(sem_DMA);

		}
	}

}


