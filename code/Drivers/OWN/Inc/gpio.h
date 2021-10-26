/*
 * gpio.h
 *
 *  Created on: Oct 23, 2021
 *      Author: lliano
 */

#ifndef OWN_INC_GPIO_H_
#define OWN_INC_GPIO_H_

#define LED_1 0
#define LED_2 1

void toggle_led(uint8_t led);
void start_buzzer(uint32_t ontime, uint32_t offtime, uint8_t ncycles);

#endif /* OWN_INC_GPIO_H_ */
