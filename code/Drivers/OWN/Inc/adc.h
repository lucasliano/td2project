/*
 * adc.h
 *
 *  Created on: Oct 26, 2021
 *      Author: lliano
 */

#ifndef OWN_INC_ADC_H_
#define OWN_INC_ADC_H_

#define CHANNEL_POWER_SUPPLY 1
#define CHANNEL_POWER_BATT 1

#define ADC_TIMEOUT 10
#define TICKS_ADC_MS		(50)
#define DELAY_ADC			(64)

void adc_init(ADC_HandleTypeDef*);
uint32_t get_adc_raw(uint8_t channel);

#endif /* OWN_INC_ADC_H_ */
