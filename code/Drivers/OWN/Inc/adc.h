/*
 * adc.h
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */

#ifndef OWN_INC_ADC_H_
#define OWN_INC_ADC_H_

#define CHANNEL_POWER_SUPPLY 1
#define CHANNEL_POWER_BATT 2

//#define LEN_MUESTRAS	(8)
//#define N_CANALES		(2)
//#define TIC_MUESTRAS_MS	(10)

typedef struct
{
	uint32_t x;
	uint32_t y;
} ejes;

#define LEN_COLA	(4)
#define N_SAMPLES	(64)
#define LEN_SERIE	(32)
#define TS_MS		(4)

void adc_init(ADC_HandleTypeDef*);
void update_adc(void);


void inic_punteros(void);
void cambiar_punteros(void);
void tarea_conversiones(void *p);
void tarea_promedia(void *p);

#endif /* OWN_INC_ADC_H_ */
