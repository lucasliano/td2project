/*
 * eeprom.c
 *
 *  Created on: Oct 16, 2021
 *      Author: lliano
 */


#include "own_drivers.h"

/* ========= Variables Globales ==============*/
/* ---------     Semaforos        ------------*/

/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
static I2C_HandleTypeDef* i2c;
/* ===========================================*/


/*
 * Function Name: init_eeprom
 * Function Description: Función que resuelve la inicialización de la eeprom.
 * Input Parameters:
 * 					I2C_HandleTypeDef *s - Handler del I2C
 * Return value: None.
 */
void init_eeprom(I2C_HandleTypeDef *s)
{
	i2c = s;
	uint8_t wbuff[EEPROM_PAGE_SIZE];

	// Escribimos toda la memoria con 0xF
	for (int page = 0; page < EEPROM_TOTAL_PAGES; page++)
	{
		for (int i = 0; i < EEPROM_PAGE_SIZE; i++)
			wbuff[i] = 255;
		eeprom_write_page(page, wbuff, EEPROM_PAGE_SIZE);
	}
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
 * 					uint8_t* data - Datos que vamos a escribir.
 * 					uint8_t size - Cantidad de bytes que queremos escribir en una pag.
 * Return value:
 * 					EEPROM_OK si funciono la escritura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t eeprom_write_page(uint8_t page, uint8_t* data, uint8_t size)
{
	uint8_t addr = EEPROM_INITIAL_ADDR + (page * EEPROM_PAGE_SIZE);

	if (size > EEPROM_PAGE_SIZE) return EEPROM_ERROR;
	return write_eeprom(addr, data, size);
}

/*
 * Function Name: eeprom_read_page
 * Function Description: Función que resuelve la lectura de paginas.
 * Input Parameters:
 * 					uint8_t page - Pagina que queremos leer.
 * 					uint8_t* rbuff - Puntero al buffer donde se guardan los datos.
 * 					uint8_t size - Cantidad de bytes que queremos leer.
 * Return value:
 * 					EEPROM_OK si funciono la lectura.
 * 					EEPROM_ERROR si no funciono.
 */
uint8_t eeprom_read_page(uint8_t page, uint8_t* rbuff, uint8_t size)
{
	uint8_t addr = EEPROM_INITIAL_ADDR + (page * EEPROM_PAGE_SIZE);

	if (size > EEPROM_PAGE_SIZE) return EEPROM_ERROR;
	return read_eeprom(addr, rbuff, size);
}




