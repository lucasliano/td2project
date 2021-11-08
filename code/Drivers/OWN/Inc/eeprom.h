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
#define EEPROM_TOTAL_PAGES 32
#define EEPROM_PAGE_SIZE 8	// En bytes
// Nota: 8bytes * 32pages = 256bytes = 2kbit

//------------ Declaraciones referidas al uso --------------
#define EEPROM_OK 0
#define EEPROM_ERROR 1

#define EEPROM_CMD_READ		0
#define EEPROM_CMD_WRITE	1
#define EEPROM_CMD_ACK		2
#define EEPROM_CMD_NACK		3

//------------------- Process ID definitions --------------
#define PID_RFID_WORKING 	0
#define PID_RFID_ADDING		1
#define PID_ADC  			2


//------------------- Paginación --------------
#define ID_INIT_PAGE		0
#define ID_BLOCK_DEPTH		2

#define PASS_INIT_PAGE		ID_INIT_PAGE+ID_BLOCK_DEPTH
#define PASS_BLOCK_DEPTH	1

#define RFID_INIT_PAGE 		PASS_INIT_PAGE+PASS_BLOCK_DEPTH
#define RFID_BLOCK_DEPTH 	1	// Cada ID son 4Byte, por ende nos entran 2 en 8Byte

#define LOGS_INIT_PAGE 		RFID_INIT_PAGE+RFID_BLOCK_DEPTH
#define LOGS_BLOCK_DEPTH	28


//--------------------- Estructuras -----------------------
 struct eeprom_message
 {
	uint8_t PID;
	uint8_t CMD_ID;
	uint8_t page;
	uint8_t offset;
	uint8_t data[EEPROM_PAGE_SIZE];
	uint8_t size;
 };

 struct eeprom_logs_block	// 4 Bytes
 {
	 RTC_TimeTypeDef hora;	// 3 Bytes
	 uint8_t evento;		// 1 Byte
 };


//------------ Declaraciones referido a tareas -----------
#define EEPROM_QUEUE_LENGTH 16
#define EEPROM_QUEUE_SIZE (sizeof(struct eeprom_message))
#define EEPROM_MAX_QUEUE_DELAY ( TickType_t ) 0

 //--------------- Functions ---------------------
void init_eeprom(I2C_HandleTypeDef *s);
uint8_t write_eeprom(uint8_t addr, uint8_t* data, uint8_t size);
uint8_t read_eeprom(uint8_t addr, uint8_t* rbuff, uint8_t size);
uint8_t eeprom_write_page(uint8_t page, uint8_t offset, uint8_t* data, uint8_t size);
uint8_t eeprom_read_page(uint8_t page, uint8_t offset, uint8_t* rbuff, uint8_t size);
void send_msg_from_eeprom(struct eeprom_message* send_msg);
uint8_t consumer_write(uint8_t PID, uint8_t page, uint8_t offset, uint8_t* data, uint8_t size);
uint8_t consumer_read(uint8_t PID, uint8_t page, uint8_t offset, uint8_t* data, uint8_t size);

#endif /* OWN_INC_EEPROM_H_ */
