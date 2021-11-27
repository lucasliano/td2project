/*
 * adc.h
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f1xx_hal.h"

#define WITH_POWER 0
#define WITHOUT_POWER 1

#define SIN_BATT 2700
#define POCA_BATT 2800
#define MEDIA_BATT 2900


#define BATERIA_DESCARGADA	0
#define BATERIA_POCA_CARGA	1
#define BATERIA_NORMAL		2
#define BATERIA_LLENA		3


typedef struct
{
	uint32_t power_supply;
	uint32_t batt;
} medidas;

#define N_SAMPLES	(32)
#define TS_MS		(10)

void adc_init(ADC_HandleTypeDef*);
void update_adc(void);


void inic_punteros(void);
void cambiar_punteros(void);
void tarea_conversiones(void *p);
void fsm_power_supply(void);
uint8_t adc_get_batt_level( void);

#endif /* INC_ADC_H_ */
