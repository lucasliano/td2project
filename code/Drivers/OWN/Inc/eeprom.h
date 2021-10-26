/*
 * eeprom.h
 *
 *  Created on: Oct 3, 2021
 *      Author: lliano
 */

#ifndef OWN_INC_EEPROM_H_
#define OWN_INC_EEPROM_H_
#include "stm32f1xx_hal.h"


//------------ Declaraciones referido al datasheet ---------
#define EEPROM_ADDRESS_I2C (0b1010000) << 1
#define EEPROM_INITIAL_ADDR 0x0
#define EEPROM_TOTAL_PAGES 16
#define EEPROM_PAGE_SIZE 16	// En bytes
// Nota: 16bytes * 16pages = 256bytes = 2kbit

//------------ Declaraciones referidas al uso --------------
#define EEPROM_OK 0
#define EEPROM_ERROR 1

#define EEPROM_CMD_READ		0
#define EEPROM_CMD_WRITE	1
#define EEPROM_CMD_ACK		2
#define EEPROM_CMD_NACK		3

//------------------- Process ID definitions --------------
#define PID_RFID 0
#define PID_ADC  1


//--------------------- Estructuras -----------------------
 struct eeprom_message
 {
	uint8_t PID;
	uint8_t CMD_ID;
	uint8_t page;
	uint8_t data[EEPROM_PAGE_SIZE];
	uint8_t size;
 };

//------------ Declaraciones referido a tareas -----------
#define EEPROM_QUEUE_LENGTH 16
#define EEPROM_QUEUE_SIZE (sizeof(struct eeprom_message))
#define EEPROM_MAX_QUEUE_DELAY ( TickType_t ) 0

 //--------------- Functions ---------------------
void init_eeprom(I2C_HandleTypeDef *s);
uint8_t write_eeprom(uint8_t addr, uint8_t* data, uint8_t size);
uint8_t read_eeprom(uint8_t addr, uint8_t* rbuff, uint8_t size);
uint8_t eeprom_write_page(uint8_t page, uint8_t* data, uint8_t size);
uint8_t eeprom_read_page(uint8_t page, uint8_t* rbuff, uint8_t size);


#endif /* OWN_INC_EEPROM_H_ */
