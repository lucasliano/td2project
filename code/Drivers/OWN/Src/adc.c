/*
 * adc.c
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */
#include "own_drivers.h"

/* ========= Variables Globales ==============*/
/* ---------     Semaforos        ------------*/

/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
static ADC_HandleTypeDef* adc;
/* ===========================================*/


void adc_init(ADC_HandleTypeDef* handler)
{
	adc = handler;
	HAL_ADCEx_Calibration_Start(adc);
}

uint32_t get_adc_raw(uint8_t channel)
{
	uint32_t raw;
	uint16_t jj;

	HAL_ADC_Start(adc);

	for(jj = 0; jj < channel+1; jj++)
	{
		HAL_ADC_PollForConversion(adc, ADC_TIMEOUT);
		HAL_Delay(DELAY_ADC);
		raw = HAL_ADC_GetValue(adc);
	}

	HAL_ADC_Stop(adc);

	return raw;
}


