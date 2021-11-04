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

#define LEN_MUESTRAS	(8)
#define N_CANALES		(2)
#define TIC_MUESTRAS_MS	(10)

void adc_init(ADC_HandleTypeDef*);
void update_adc(void);

#endif /* OWN_INC_ADC_H_ */
