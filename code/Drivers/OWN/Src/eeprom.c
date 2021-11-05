/*
 * eeprom.c
 *
 *  Created on: Oct 16, 2021
 *      Author: lliano
 */


#include "own_drivers.h"

/* ========= Variables Globales ==============*/
extern uint8_t clave[4];

/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_clave;

/* ---------  Colas de mensaje    ------------*/
extern xQueueHandle queue_from_eeprom;
extern xQueueHandle queue_to_eeprom;

/* ---------  Variables de estado ------------*/
static I2C_HandleTypeDef* i2c;
/* ===========================================*/


/*
 * Function Name: init_eeprom
 * Function Description: Función que resuelve la inicialización de la eeprom y su contenido inicial.
 * Input Parameters:
 * 					I2C_HandleTypeDef *s - Handler del I2C
 * Return value: None.
 */
void init_eeprom(I2C_HandleTypeDef *s)
{
	i2c = s;
	uint8_t wbuff[EEPROM_PAGE_SIZE];

	uint16_t id = 0xABCD;

	// Escribimos toda la memoria con 0xFF
	for (uint8_t page = 0; page < EEPROM_TOTAL_PAGES; page++)
	{
		for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
			wbuff[i] = 255;
		eeprom_write_page(page, 0, wbuff, EEPROM_PAGE_SIZE);
		HAL_Delay(10);
	}

	// Cargo valores por default de Signature
	memcpy(wbuff, "tecnicas",8);
	eeprom_write_page(ID_INIT_PAGE, 0, wbuff, EEPROM_PAGE_SIZE);
	HAL_Delay(10);

	for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
		wbuff[i] = 0;

	memcpy(wbuff, "digitale",8);
	eeprom_write_page(ID_INIT_PAGE+1, 0, wbuff, EEPROM_PAGE_SIZE);
	HAL_Delay(10);

	for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
		wbuff[i] = 0;

	// Cargo valor por default de password
	memcpy(clave, "1234",8);
	memcpy(wbuff, "1234XXXX",8);
	eeprom_write_page(PASS_INIT_PAGE, 0, wbuff, EEPROM_PAGE_SIZE);
	HAL_Delay(10);

	for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
		wbuff[i] = 0;

	// Cargo valor por default de Tarjeta ID
	memcpy(wbuff, &id , 2);	// Nota: Debido al endianess, se guarda LSB primero
	eeprom_write_page(RFID_INIT_PAGE, 0, wbuff, EEPROM_PAGE_SIZE);
	HAL_Delay(10);


//	uint8_t rbuff[EEPROM_PAGE_SIZE];
//	for (uint8_t page = 0; page < EEPROM_TOTAL_PAGES; page++)
//	{
//		for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
//			rbuff[i] = 0;
//		eeprom_read_page(page, 0, rbuff, EEPROM_PAGE_SIZE);
//		HAL_Delay(10);
//	}
}

/*
 * Function Name: write_eeprom
 * Function Description: Función que resuelve la escritura a la eeprom.
 * Input Parameters:
 * 					uint8_t addr - Dirección de memoria a escribir.
 * 					uint8_t* data - Datos que queremos escribir.
 * 					uint8_t size - Cantidad de bytes que queremos escribir
 * Return value:
 * 					EEPROM_OK si funciono la escritura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t write_eeprom(uint8_t addr, uint8_t* data, uint8_t size)
{
	uint8_t ret = HAL_ERROR;

	ret =  HAL_I2C_Mem_Write(i2c, EEPROM_ADDRESS_I2C,
							 addr, I2C_MEMADD_SIZE_8BIT,
							 data, size, HAL_MAX_DELAY);
	if (ret != HAL_OK) return EEPROM_ERROR;

	return EEPROM_OK;
}

/*
 * Function Name: read_eeprom
 * Function Description: Función que resuelve la lectura a la eeprom.
 * Input Parameters:
 * 					uint8_t addr - Dirección de memoria a leer.
 * 					uint8_t* rbuff - Puntero al buffer donde se guardan los datos.
 * 					uint8_t size - Cantidad de bytes que queremos leer.
 * Return value:
 * 					EEPROM_OK si funciono la lectura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t read_eeprom(uint8_t addr, uint8_t* rbuff, uint8_t size)
{
	uint8_t ret = HAL_ERROR;

	ret =  HAL_I2C_Mem_Read(i2c, EEPROM_ADDRESS_I2C,
							addr, I2C_MEMADD_SIZE_8BIT, rbuff,
							size,  HAL_MAX_DELAY);
	if (ret != HAL_OK) return EEPROM_ERROR;

	return EEPROM_OK;
}

/*
 * Function Name: eeprom_write_page
 * Function Description: Función que resuelve la escritura de paginas a nivel de primitiva.
 * Input Parameters:
 * 					uint8_t page - Página que queremos escribir.
 * 					uint8_t offset - A partir de cual byte de la pagina queremos escribir.
 * 					uint8_t* data - Datos que vamos a escribir.
 * 					uint8_t size - Cantidad de bytes que queremos escribir en una pag.
 * Return value:
 * 					EEPROM_OK si funciono la escritura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t eeprom_write_page(uint8_t page, uint8_t offset, uint8_t* data, uint8_t size)
{
	uint8_t addr = EEPROM_INITIAL_ADDR + (page * EEPROM_PAGE_SIZE) + offset;

	if (offset > EEPROM_PAGE_SIZE)	return EEPROM_ERROR;
	if (size > EEPROM_PAGE_SIZE-offset) return EEPROM_ERROR;
	return write_eeprom(addr, data, size);
}

/*
 * Function Name: eeprom_read_page
 * Function Description: Función que resuelve la lectura de paginas.
 * Input Parameters:
 * 					uint8_t page - Pagina que queremos leer.
 * 					uint8_t offset - A partir de cual byte de la pagina queremos leer.
 * 					uint8_t* rbuff - Puntero al buffer donde se guardan los datos.
 * 					uint8_t size - Cantidad de bytes que queremos leer.
 * Return value:
 * 					EEPROM_OK si funciono la lectura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t eeprom_read_page(uint8_t page, uint8_t offset, uint8_t* rbuff, uint8_t size)
{
	uint8_t addr = EEPROM_INITIAL_ADDR + (page * EEPROM_PAGE_SIZE);

	if (offset > EEPROM_PAGE_SIZE)	return EEPROM_ERROR;
	if (size > EEPROM_PAGE_SIZE-offset) return EEPROM_ERROR;
	return read_eeprom(addr, rbuff, size);
}



/*
 * Function Name: send_msg_from_eeprom
 * Function Description: Función que carga en la cola queue_from_eeprom mensajes a enviar..
 * Input Parameters:
 * 					struct eeprom_message* send_msg - Estructura con mensaje cargado para enviar.
 * Return value:
 * 					None.
 */
void send_msg_from_eeprom(struct eeprom_message* send_msg)
{
	uint8_t space_available = 0;
	uint8_t status;

	do{
		vTaskDelay(10);
		space_available = uxQueueSpacesAvailable(queue_from_eeprom);
	}while(!space_available);

	status = xQueueSend(queue_from_eeprom, send_msg, EEPROM_MAX_QUEUE_DELAY);
	if (status == errQUEUE_FULL){
		Error_Handler();
	}
}


