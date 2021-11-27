/*
 * gpio.h
 *
 *  Created on: Oct 23, 2021
 *      Author: lliano
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define LED_1 0
#define LED_2 1

#define LED_ON	GPIO_PIN_RESET
#define LED_OFF	GPIO_PIN_SET

void led_init(void);
void toggle_led(uint8_t led);
void start_buzzer(uint32_t ontime, uint32_t offtime, uint8_t ncycles);

#endif /* INC_GPIO_H_ */
