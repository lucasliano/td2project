/*
 * gpio.c
 *
 *  Created on: Oct 23, 2021
 *      Author: lliano
 */
#include "own_drivers.h"

void toggle_led(uint8_t led)
{
	switch(led)
	{
	case LED_1:
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
		break;
	case LED_2:
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
		break;
	default:
		Error_Handler();
	}
}

void start_buzzer(uint32_t ontime, uint32_t offtime, uint8_t ncycles)
{
	uint8_t jj;
	for(jj = 0; jj < ncycles; jj++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		vTaskDelay(ontime);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		vTaskDelay(offtime);
	}

}
