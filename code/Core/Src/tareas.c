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
	while(1)
	{
		vTaskDelay(1000);
	}
}

void detectar_rfid(void *p)
/*
 * ======== detectar_rfid =============
 * Tarea global. Contiene la máquina de estados que se encarga de realizar las validaciones correspondientes con el periférico RFID
 *
 * -------- Conexiones ----------------
 * 		RC522		BP
 * 		-----		--
 * 		SDA	 ->		B12
 * 		SCK	 ->		B13
 * 		MOSI ->		B15
 * 		MISO ->		B14
 * 		IRQ	 ->		--
 * 		GND	 ->		G
 * 		RST	 ->		--
 * 		3.3V -> 	3.3
 *
 * -------- Uso de memoria -------------
 * Stack size:
 * 				uint8_t status 		-> 8 bytes
 * 				uint8_t cardstr[17] -> 8*17 = 136  bytes
 * 				uint8_t id[4]  		-> 8*4 = 32 bytes
 * 				========================================
 * Total:							-> 176 bytes
 */
{
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
			HAL_Delay(2);
			MFRC522_Anticoll(cardstr);
			id[0] = cardstr[0];
			id[1] = cardstr[1];
			id[2] = cardstr[2];
			id[3] = cardstr[3];
			MFRC522_Halt();
			HAL_Delay(2);
		}
		vTaskDelay(10);
	}
	UNUSED(id); // Esto evita que el compilador tire warnings
}

void detectar_sensores(void *p)
{
	// (Dependiendo del estado de la alarma, debe hacer sonar el buzzer)
	while(1)
	{
		vTaskDelay(1000);
	}
}

void conexion_bt(void *p)
{
	// Maquinas de estados con ESPERANDO_CONEXION - ESPERANDO_COMANDO - ACTUANDO
	while(1)
	{
		vTaskDelay(1000);
	}
}

void checkear_power_supply(void *p)
{
	// Lectura ADC
	while(1)
	{
		vTaskDelay(1000);
	}
}

void escritura_eeprom(void *p)
{
	// Cola de mensajes
//	xQueueReceive(cola_tiempo, &item, portMAX_DELAY);
//	vTaskDelay(item);
//	xQueueSend(cola_todo_piola,&ok,portMAX_DELAY);
	while(1)
	{
		vTaskDelay(1000);
	}
}

void lcd_update(void *p)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}

//void lectura_eeprom(void *p)
//{
//
//}

//void actualizar_nivel_bateria(void *p)
//{
//
//}

