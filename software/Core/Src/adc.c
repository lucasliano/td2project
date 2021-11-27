/*
 * adc.c
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */
#include <own_drivers.h>

/* ========= Variables Globales ==============*/
extern uint16_t datos_adc_1[N_SAMPLES];
extern uint16_t datos_adc_2[N_SAMPLES];
extern uint16_t *datos_adc_dma, *datos_adc_uso;

extern medidas adc_buffer;
/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_DMA;
/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
static ADC_HandleTypeDef* adc;
/* ===========================================*/

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	BaseType_t pxTaskWoken;
	cambiar_punteros();
	xSemaphoreGiveFromISR(sem_DMA,&pxTaskWoken);
	portEND_SWITCHING_ISR(pxTaskWoken);
}


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
	adc_buffer.power_supply = 0xFFFFFFFF;
	adc_buffer.batt = 0xFFFFFFFF;

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

void update_adc(void)
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
		adc_buffer.power_supply = x;
		adc_buffer.batt = y;
	}
}

void fsm_power_supply(void)
{
	static uint8_t state;

	switch(state)
	{
		case WITH_POWER:
			if (adc_buffer.power_supply < 1000)
			{
				save_event(EVENT_POWER_OFF);
				state = WITHOUT_POWER;
			}
			break;
		case WITHOUT_POWER:
			if (adc_buffer.power_supply > 2500)
			{
				save_event(EVENT_POWER_ON);
				state = WITH_POWER;
			}
			break;

		default:
			state = WITH_POWER;
	}
}

uint8_t adc_get_batt_level( void)
{
	if ( adc_buffer.batt < SIN_BATT){
		return BATERIA_DESCARGADA;
	}else if ( adc_buffer.batt < POCA_BATT){
		return BATERIA_POCA_CARGA;
	}else if ( adc_buffer.batt < MEDIA_BATT){
		return BATERIA_NORMAL;
	}else
	{
		return BATERIA_LLENA;
	}
}


