/**
  ******************************************************************************
  * @file           : tareas.c
  * @brief          : Archivo donde se programan las tareas a nivel de aplicación
  ******************************************************************************
**/
#include "main.h"
#include "cmsis_os.h"

void checkear_teclado(void *p)
{

}

void detectar_rfid(void *p)
{
	// Stack size:
	//				uint8_t status 		-> 8 bytes
	//				uint8_t cardstr[17] -> 8*17 = 136  bytes
	//				uint8_t id[4]  		-> 8*4 = 32 bytes
	//				========================================
	//		Total:						-> 176 bytes

	uint8_t status;
	uint8_t cardstr[MAX_LEN+1];
	uint8_t id[4];
	while(1)
	{
		status = 0;
		memset(cardstr,0,sizeof(cardstr));
		status = (uint8_t) MFRC522_Request(PICC_REQIDL, cardstr);
		if (status == MI_OK)
		{
			vTaskDelay(1000);
		}
		vTaskDelay(100);
	}

	/*
	* Conexiones:
	* ----------
	*
	* RC522			BP
	* -----			--
	* SDA	->		A4
	* SCK	->		A5
	* MOSI	->		A7
	* MISO	->		A6
	* IRQ	->		Sin conectar
	* GND	->		G
	* RST	->		A3
	* 3.3V	-> 		3.3
	*/

}

void detectar_sensores(void *p)
{
	// (Dependiendo del estado de la alarma, debe hacer sonar el buzzer)
}

void conexion_bt(void *p)
{
	// Maquinas de estados con ESPERANDO_CONEXION - ESPERANDO_COMANDO - ACTUANDO
}

void checkear_power_supply(void *p)
{
	// Lectura ADC
}

void escritura_eeprom(void *p)
{
	// Cola de mensajes
//	xQueueReceive(cola_tiempo, &item, portMAX_DELAY);
//	vTaskDelay(item);
//	xQueueSend(cola_todo_piola,&ok,portMAX_DELAY);
}

void lcd_update(void *p)
{

}

//void lectura_eeprom(void *p)
//{
//
//}

//void actualizar_nivel_bateria(void *p)
//{
//
//}

