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
extern medidas adc_buffer;
extern uint8_t rfid_internal_state;
uint8_t estado_global = APAGADO;
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
                    start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[0][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[0][1])){
					tecla[i] = '2';
					i++;
                    start_buzzer(200, 200, 1);
			}

			chequear_arrebote(&boton[0][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[0][2]))
			{
					tecla[i] = '3';
					i++;
					start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[0][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[0][3])){
					tecla[i] = 'A';
					i++;
                    start_buzzer(200, 200, 1);
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
                    start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[1][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[1][1])){
					tecla[i] = '5';
					i++;
                    start_buzzer(200, 200, 1);
			}

			chequear_arrebote(&boton[1][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[1][2]))
			{
					tecla[i] = '6';
					i++;
					start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[1][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[1][3])){
					tecla[i] = 'B';
					i++;
                    start_buzzer(200, 200, 1);
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
                    start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[2][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[2][1])){
					tecla[i] = '8';
					i++;
                    start_buzzer(200, 200, 1);
			}

			chequear_arrebote(&boton[2][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[2][2]))
			{
					tecla[i] = '9';
					i++;
					start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[2][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[2][3])){
					tecla[i] = 'C';
					i++;
                    start_buzzer(200, 200, 1);
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
                    start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[3][1], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA2));
			if(hay_flanco_arrebote(&boton[3][1])){
					tecla[i] = '0';
					i++;
                    start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[3][2], HAL_GPIO_ReadPin(PUERTO_COLUMNA123,COLUMNA3));
			if(hay_flanco_arrebote(&boton[3][2]))
			{
					tecla[i] = '#';
					i++;
					start_buzzer(200, 200, 1);
			}
			chequear_arrebote(&boton[3][3], HAL_GPIO_ReadPin(PUERTO_COLUMNA4,COLUMNA4));
			if(hay_flanco_arrebote(&boton[3][3])){
					tecla[i] = 'D';
					i++;
                    start_buzzer(200, 200, 1);
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
				toggle_led(LED_2);
				while( rfid_find_card((uint8_t*) &new_id) != CARD_DETECTED);
				status = rfid_add_id(new_id);
				rfid_internal_state = WORKING_STATE;
				toggle_led(LED_2);
				start_buzzer(200, 100, 2);
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

	for(;;){
		switch(estado_global){
		case APAGADO:
			xSemaphoreTake(sem_state,portMAX_DELAY);
			if(clave_ok){
				estado_global = ENCENDIDIO;
				clave_ok = 0; //Bajo el flag
				toggle_led(LED_1);
				save_event(EVENT_ALARM_ON);
				start_buzzer(100, 100, 3);
			}
			xSemaphoreGive(sem_state);
			break;

		case ENCENDIDIO:
			if(leer_sensor(1)){
				// Area 2
				save_event(EVENT_ALARM_BEEP_SALA1);
				estado_global = ALARMANDO;
			}
			if(leer_sensor(2)){
				// Area 2
				save_event(EVENT_ALARM_BEEP_SALA2);
				estado_global = ALARMANDO;
			}

			xSemaphoreTake(sem_state,portMAX_DELAY);
			if(clave_ok){
				estado_global = APAGADO;
				clave_ok = 0; //Bajo el flag
				save_event(EVENT_ALARM_OFF);
				toggle_led(LED_1);
				start_buzzer(100, 100, 3);
			}
			xSemaphoreGive(sem_state);
			break;

		case ALARMANDO:

			start_buzzer(100, 100, 5);

			xSemaphoreTake(sem_state,portMAX_DELAY);
			if(clave_ok){
				estado_global = APAGADO;
				clave_ok = 0; //Bajo el flag
				save_event(EVENT_ALARM_OFF);
				toggle_led(LED_1);
			}
			xSemaphoreGive(sem_state);
			break;

		default:
			estado_global = APAGADO;
			clave_ok = 0;
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
		fsm_power_supply();

		vTaskDelay(10);
	}
}



void lcd_update(void *p)
{
	char hora_str[64];
	char batt_char[] = {(char)0xFF};
	uint8_t batt_level = 0;
	RTC_TimeTypeDef hora;

	for (uint8_t jj = 0; jj < 8; jj++)
	{
		hora_str[jj] = 'X';
	}

	while(1)
	{
		lcd_clear ();
		vTaskDelay(30);

		lcd_cursor(0, 0);
		lcd_send_string ("HORA:",5);
		vTaskDelay(30);


		hora = obtener_tiempo();
		sprintf(hora_str, "%02d:%02d:%02d", hora.Hours, hora.Minutes, hora.Seconds);

		lcd_cursor(0,7);
		lcd_send_string (hora_str,8);

		lcd_cursor(1, 0);
		lcd_send_string ("BATERIA: |   |",14);
		vTaskDelay(30);

		batt_level = adc_get_batt_level();
		for (uint8_t i = 0; i < batt_level; i++)
		{
			lcd_cursor(1, 10 + i);
			lcd_send_string (batt_char,1);
			vTaskDelay(30);
		}

		vTaskDelay(1000);
	}
}

void tarea_serie(void *p)
/*
 * 	Trama utilizada:
 * 		1b 	 - '$' 		- Inicio de trama
 * 		Yb	 - clave	- Clave para desbloquear el sistema. Largo = LARGO_CLAVE
 * 		1b 	 - cmd		- Comando
 * 		Nb	 - datos	- LEN_BUFFER_RX bytes max
 * 		0xD	 - 'CR'		- fin de trama x1
 * 		0xA	 - 'LF'		- fin de trama x2
 */

{
	uint8_t byte_recibido = 0x0;
	static uint8_t estado = ESPERANDO_INICIO;
	static uint8_t contador = 0;
	static uint8_t local_clave[LARGO_CLAVE+1];
	static uint8_t datos[6];
	static uint8_t cmd = 255;

	while(1)
	{
		byte_recibido = serieFreeRTOS_getchar();
		switch(estado)
		{
			case ESPERANDO_INICIO:
				if (byte_recibido == '$')
				{
					estado = ESPERANDO_CLAVE;
					for (uint8_t i = 0; i < LEN_BUFFER_RX; i++)
						datos[i] = 'q';
				}
				break;
			case ESPERANDO_CLAVE:
				if (contador < LARGO_CLAVE-1)
				{
					local_clave[contador] = byte_recibido;
					contador++;
				}else{
					local_clave[contador] = byte_recibido;
					contador = 0;
					local_clave[LARGO_CLAVE] = '#';
					if(chequear_clave(local_clave) ){
						estado = ESPERANDO_CMD;
					}
					else{
						estado = ESPERANDO_INICIO;
					}
				}
				break;
			case ESPERANDO_CMD:
				cmd = byte_recibido;
				estado = ESPERANDO_DATOS;
				break;
			case ESPERANDO_DATOS:
				switch(cmd)
				{
					case CMD_CLAVE:
						if (contador < LARGO_CLAVE-1)
						{
							datos[contador] = byte_recibido;
							contador++;

							//Filtro de valores numericos
							if (byte_recibido < 48 || byte_recibido > 57)
							{
								contador = 0;
								estado = ESPERANDO_INICIO;
								cmd = 255;
							}
						}else{
							datos[contador] = byte_recibido;
							contador = 0;
							estado = ESPERANDO_FIN1;
						}
						break;
					case CMD_RFID:
						if (byte_recibido == 'R')
						{
							estado = ESPERANDO_FIN1;
						}else{
							estado = ESPERANDO_INICIO;
							cmd = 255;
						}
						break;
					case CMD_MEM:
						if (byte_recibido == 'M')
						{
							estado = ESPERANDO_FIN1;
						}else{
							estado = ESPERANDO_INICIO;
							cmd = 255;
						}
						break;
					case CMD_HORA:
						if (contador < 6-1)
						{
							datos[contador] = byte_recibido;
							contador++;

							//Filtro de valores numericos
							if (byte_recibido < 48 || byte_recibido > 57)
							{
								contador = 0;
								estado = ESPERANDO_INICIO;
								cmd = 255;
							}
						}else{
							datos[contador] = byte_recibido;
							contador = 0;
							estado = ESPERANDO_FIN1;
						}
						break;
					default:
						estado = ESPERANDO_INICIO;
						cmd = 255;
				}
				break;
			case ESPERANDO_FIN1:
				if (byte_recibido == 0xD)
				{
					estado = ESPERANDO_FIN2;
				}else{
					estado = ESPERANDO_INICIO;
					cmd = 255;
				}
				break;
			case ESPERANDO_FIN2:
				if (byte_recibido == 0xA)
				{
					serie_ejecutar(cmd, datos);
				}
				estado = ESPERANDO_INICIO;
				cmd = 255;
				break;
			default:
				estado = ESPERANDO_INICIO;
				cmd = 255;
				contador = 0;
				break;
		}
		vTaskDelay(1);
	}
}

void serie_ejecutar(uint8_t comando, uint8_t* datos)
{
	struct eeprom_logs_block eventos[LOGS_SIZE];
	RTC_TimeTypeDef time;
	if (estado_global != APAGADO) return;
	switch(comando)
	{
		case CMD_CLAVE:
			eeprom_save_pass(datos);
			break;
		case CMD_RFID:
			rfid_internal_state = ADDING_CARD_STATE;
			break;
		case CMD_MEM:
			get_events(eventos);
			for (uint8_t i = 0; i < LOGS_SIZE; i++)
			{
				if (eventos[i].evento != 255)
				{
					serieFreeRTOS_putchar('$');
					serieFreeRTOS_putchar(eventos[i].evento);
					serieFreeRTOS_putchar(eventos[i].hora.Hours);
					serieFreeRTOS_putchar(eventos[i].hora.Minutes);
					serieFreeRTOS_putchar(eventos[i].hora.Seconds);
					serieFreeRTOS_putchar(0xD);
					serieFreeRTOS_putchar(0xA);
				}
			}
			vTaskDelay(3000);
			break;
		case CMD_HORA:
			time.Hours = string_to_int(datos);
			time.Minutes = string_to_int(datos+2);
			time.Seconds = string_to_int(datos+4);
			rtc_update(time);
			break;
	}
}



