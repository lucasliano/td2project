/**
  ******************************************************************************
  * @file           : tareas.c
  * @brief          : Archivo donde se programan las tareas a nivel de aplicación
  ******************************************************************************
**/
#include "main.h"
#include "cmsis_os.h"

/* ========= Variables Globales ==============*/
/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_state;

/* ---------  Colas de mensaje    ------------*/
extern xQueueHandle queue_from_eeprom;
extern xQueueHandle queue_to_eeprom;


/* ---------  Variables de estado ------------*/
extern arrebote boton[4][4];
extern uint8_t clave_ok;
extern uint8_t rfid_internal_state;
/* ===========================================*/

void checkear_teclado(void *p)
/*
 * ======== checkear_teclado =============
 * Tarea global.
 *
 *
 */
{
	uint8_t tecla[LARGO_CLAVE+1] = {0}; //Cuento el # de cierre
	uint8_t i=0;

	uint8_t estado = 0;

	for(;;){

		//Chequeo si esta la clave y si funciona OK
		if (i == (LARGO_CLAVE+1)){
			i=0;
			if(chequear_clave(tecla) ){
				xSemaphoreTake(sem_state,portMAX_DELAY);
				clave_ok = 1;
				xSemaphoreGive(sem_state);
			}
			else{
				xSemaphoreTake(sem_state,portMAX_DELAY);
				clave_ok = 0;
				xSemaphoreGive(sem_state);
			}
		}

		switch(estado){
		case 0:
			HAL_GPIO_WritePin(PUERTO_FILA,FILA1,GPIO_PIN_SET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA2,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA3,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA4,GPIO_PIN_RESET );
			//Leo las columnas
			chequear_arrebote(&boton[0][0], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA1));
			if(hay_flanco_arrebote(&boton[0][0])){
					tecla[i] = '1';
					i++;
			}
			chequear_arrebote(&boton[0][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[0][1])){
					tecla[i] = '2';
					i++;
			}

			chequear_arrebote(&boton[0][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[0][2]))
				{
					tecla[i] = '3';
					i++;
				}
			chequear_arrebote(&boton[0][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[0][3])){
					tecla[i] = 'A';
					i++;
			}

			estado = 1;
			//vTaskDelay(DEMORA_LECTURA / portTICK_RATE_MS);
			break;
		case 1:
			HAL_GPIO_WritePin(PUERTO_FILA,FILA1,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA2,GPIO_PIN_SET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA3,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA4,GPIO_PIN_RESET );
			//Leo las columnas
			chequear_arrebote(&boton[1][0], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA1));
			if(hay_flanco_arrebote(&boton[1][0])){
					tecla[i] = '4';
					i++;
			}
			chequear_arrebote(&boton[1][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[1][1])){
					tecla[i] = '5';
					i++;
			}

			chequear_arrebote(&boton[1][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[1][2]))
				{
					tecla[i] = '6';
					i++;
				}
			chequear_arrebote(&boton[1][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[1][3])){
					tecla[i] = 'B';
					i++;
			}
			estado = 2;
			//vTaskDelay(DEMORA_LECTURA / portTICK_RATE_MS);
			break;
		case 2:
			HAL_GPIO_WritePin(PUERTO_FILA,FILA1,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA2,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA3,GPIO_PIN_SET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA4,GPIO_PIN_RESET );
			//Leo las columnas
			chequear_arrebote(&boton[2][0], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA1));
			if(hay_flanco_arrebote(&boton[2][0])){
					tecla[i] = '7';
					i++;
			}
			chequear_arrebote(&boton[2][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[2][1])){
					tecla[i] = '8';
					i++;
			}

			chequear_arrebote(&boton[2][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[2][2]))
				{
					tecla[i] = '9';
					i++;
				}
			chequear_arrebote(&boton[2][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[2][3])){
					tecla[i] = 'C';
					i++;
			}
			estado = 3;
			//vTaskDelay(DEMORA_LECTURA / portTICK_RATE_MS);
			break;
		case 3:
			HAL_GPIO_WritePin(PUERTO_FILA,FILA1,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA2,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA3,GPIO_PIN_RESET );
			HAL_GPIO_WritePin(PUERTO_FILA,FILA4,GPIO_PIN_SET );
			//Leo las columnas
			chequear_arrebote(&boton[3][0], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA1));
			if(hay_flanco_arrebote(&boton[3][0])){
					tecla[i] = '*';
					i++;
			}
			chequear_arrebote(&boton[3][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[3][1])){
					tecla[i] = '0';
					i++;
			}
			chequear_arrebote(&boton[3][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[3][2]))
				{
					tecla[i] = '#';
					i++;
				}
			chequear_arrebote(&boton[3][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[3][3])){
					tecla[i] = 'D';
					i++;
			}
			estado = 0;
			//vTaskDelay(DEMORA_LECTURA / portTICK_RATE_MS);
			break;
		}
		vTaskDelay(DEMORA_LECTURA / portTICK_RATE_MS);

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
 */
{
	uint8_t status;
	uint32_t new_id;

	while(1)
	{
		switch(rfid_internal_state)
		{
			case WORKING_STATE:
				rfid_toggle_state();
				break;
			case ADDING_CARD_STATE:
				while( rfid_find_card((uint8_t*) &new_id) != CARD_DETECTED);
				status = rfid_add_id(new_id);
				rfid_internal_state = WORKING_STATE;
				break;
		}

		vTaskDelay(10);
	}
}

void detectar_sensores(void *p)
/*
 * ======== detectar_sensores =============
 * Tarea global.
 *
 *
 */
{
	// (Dependiendo del estado de la alarma, debe hacer sonar el buzzer)
	uint8_t estado=0;

	for(;;){
		switch(estado){
		case 0:				//APAGADO
			xSemaphoreTake(sem_state,portMAX_DELAY);
			if(clave_ok){
				estado=1;
				clave_ok = 0; //Bajo el flag
				toggle_led(LED_1);
				save_event(EVENT_ALARM_ON);
				start_buzzer(500, 500, 5);
			}
			xSemaphoreGive(sem_state);
			break;

		case 1:				//ENCENDIDO
			/*if(leer_sensor(1)){

			}
			if(leer_sensor(2)){

			}*/
			xSemaphoreTake(sem_state,portMAX_DELAY);
			if(clave_ok){
				estado=0;
				clave_ok = 0; //Bajo el flag
				save_event(EVENT_ALARM_OFF);
				toggle_led(LED_1);
			}
			xSemaphoreGive(sem_state);
			break;

		}
		vTaskDelay(DEMORA_SENSOR / portTICK_RATE_MS);
	}
}

void checkear_power_supply(void *p)
{
	while(1)
	{
		update_adc();
		vTaskDelay(100);

	}
}



void lcd_update(void *p)
{
	while(1)
	{
		char str[16];

		lcd_clear();
		lcd_cursor(0, 0);
		lcd_send_string ("HORA:",5);

//		hora_to_str(obtener_tiempo(), str);
//		lcd_cursor(0,7);
//		lcd_send_string (str,8);
//		lcd_cursor(1, 0);

		vTaskDelay(1000);
	}
}


void actualizar_nivel_bateria(void *p)
{
//	uint8_t status;
//	uint8_t data[8];
//
//	while(1)
//	{
//		for (uint8_t i = 0; i < 8; i++)
//			data[i] = 0;
//		status = consumer_read(PID_RFID, LOGS_INIT_PAGE, 0, data, EEPROM_PAGE_SIZE);
//		vTaskDelay(100);
//	}
}

void conexion_bt(void *p)
{
//	// Maquinas de estados con ESPERANDO_CONEXION - ESPERANDO_COMANDO - ACTUANDO


//	uint32_t current_value = 1;
//	uint8_t data[4];
//	uint8_t status;
//
//	while(1)
//	{
//		current_value ^= current_value << 13;
//		current_value ^= current_value >> 17;
//		current_value ^= current_value << 5;
//		for (uint8_t i = 0; i < 4; i++)
//			data[i] = (uint8_t)( (current_value >> 8*i) & 0xFF );
//
//		status = consumer_write(PID_ADC, LOGS_INIT_PAGE, 2, data, 4);
//
//		vTaskDelay(100);
//	}
}



