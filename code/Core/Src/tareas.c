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
extern xSemaphoreHandle sem_clave;

/* ---------  Colas de mensaje    ------------*/
extern xQueueHandle queue_from_eeprom;
extern xQueueHandle queue_to_eeprom;


/* ---------  Variables de estado ------------*/
extern arrebote boton[4][4];
extern uint8_t clave_ok;
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
				xSemaphoreTake(sem_clave,portMAX_DELAY);
				clave_ok = 1;
				xSemaphoreGive(sem_clave);
			}
			else{
				xSemaphoreTake(sem_clave,portMAX_DELAY);
				clave_ok = 0;
				xSemaphoreGive(sem_clave);
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

	while(1)
	{
		rfid_toggle_state();
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
			xSemaphoreTake(sem_clave,portMAX_DELAY);
							if(clave_ok){
								estado=1;
								clave_ok = 0; //Bajo el flag
								toggle_led(LED_1);
							}
			xSemaphoreGive(sem_clave);
			break;

		case 1:				//ENCENDIDO
			/*if(leer_sensor(1)){

			}
			if(leer_sensor(2)){

			}*/
			xSemaphoreTake(sem_clave,portMAX_DELAY);
							if(clave_ok){
								estado=0;
								clave_ok = 0; //Bajo el flag
								toggle_led(LED_1);
								start_buzzer(500, 500, 5);
							}
			xSemaphoreGive(sem_clave);
			break;

		}
		vTaskDelay(DEMORA_SENSOR / portTICK_RATE_MS);
	}
}

void conexion_bt(void *p)
{
//	// Maquinas de estados con ESPERANDO_CONEXION - ESPERANDO_COMANDO - ACTUANDO
//	struct eeprom_message send_msg;
//	struct eeprom_message recv_msg;
//	uint8_t status;
//	uint32_t current_value = 1;
//	uint8_t space_available = 0;

	while(1)
	{
//		space_available = uxQueueSpacesAvailable(queue_to_eeprom);
//
//		if (space_available > 0)
//		{
//			current_value ^= current_value << 13;
//			current_value ^= current_value >> 17;
//			current_value ^= current_value << 5;
//
//			send_msg.PID 	= PID_RFID;
//			send_msg.CMD_ID = EEPROM_CMD_WRITE;
//			send_msg.page 	= 3;
//			for (int j = 0; j < 3; j++)
//				send_msg.data[j]= (uint8_t) (current_value >> j*8) & 0xF;
//			for (int j = 3; j < EEPROM_PAGE_SIZE; j++)
//				send_msg.data[j] = 0;
//			send_msg.size 	= EEPROM_PAGE_SIZE;
//
//			status = xQueueSend(queue_to_eeprom, &send_msg, EEPROM_MAX_QUEUE_DELAY);
//			if (status == errQUEUE_FULL){
//				Error_Handler();
//			}
//
//			do{
//				status = xQueuePeek(queue_from_eeprom, &recv_msg, EEPROM_MAX_QUEUE_DELAY);
//				if (status == pdTRUE){
//					if(recv_msg.PID == PID_RFID)
//					{
//						status = xQueueReceive(queue_from_eeprom, &recv_msg, EEPROM_MAX_QUEUE_DELAY);
//					}else{
//						status = pdFALSE;
//					}
//				}
//				vTaskDelay(10);
//			}while(status != pdTRUE);
//		}

		vTaskDelay(100);
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


void manejo_eeprom(void *p)
/*
 * ======== manejo_eeprom =============
 * Tarea orientada a resolver el problema de escrituras y lecturas a la eeprom por varios
 * consumidores. Se utilizan colas con dicho proposito.
 *
 *
 */
{

	// Cola de mensajes
	uint8_t rbuff [EEPROM_PAGE_SIZE];
	uint8_t wbuff [EEPROM_PAGE_SIZE];
	uint8_t i2c_status;
	uint8_t status;
	struct eeprom_message recv_msg;
	struct eeprom_message send_msg;


	while(1)
	{
		i2c_status = EEPROM_ERROR;
		status = xQueueReceive(queue_to_eeprom, &recv_msg, EEPROM_MAX_QUEUE_DELAY);
		if (status == pdTRUE)
		{
			switch(recv_msg.CMD_ID)
			{
				case EEPROM_CMD_READ:
					i2c_status = eeprom_read_page(recv_msg.page, 0, rbuff, recv_msg.size);
					if (i2c_status == EEPROM_ERROR) Error_Handler();
					send_msg.PID 	= recv_msg.PID;
					send_msg.CMD_ID = EEPROM_CMD_ACK;	//ACK
					send_msg.page 	= recv_msg.page;
					for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
						send_msg.data[j] = rbuff[j];
					send_msg.size 	= recv_msg.size;

					send_msg_from_eeprom(&send_msg);

					break;

				case EEPROM_CMD_WRITE:
					for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
						wbuff[j] = recv_msg.data[j];
					i2c_status = eeprom_write_page(recv_msg.page, 0, wbuff, recv_msg.size);
					if (i2c_status == EEPROM_ERROR) Error_Handler();

					vTaskDelay(100);
					i2c_status = eeprom_read_page(recv_msg.page, 0, rbuff, recv_msg.size);
					if (i2c_status == EEPROM_ERROR) Error_Handler();

					for (int i = 0; i < recv_msg.size; i++)
					{
						if(rbuff[i] != recv_msg.data[i]) // Si lo que escribiste es distinto a lo leido
						{
							send_msg.PID 	= recv_msg.PID;
							send_msg.CMD_ID = EEPROM_CMD_NACK;	//ERROR
							send_msg.page 	= 0;
							for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
								send_msg.data[j] = 0;
							send_msg.size 	= 0;

							send_msg_from_eeprom(&send_msg);
							break;
						}
					}

					// Si llegamos acá es porque se escribió bien.
					send_msg.PID 	= recv_msg.PID;
					send_msg.CMD_ID = EEPROM_CMD_ACK;	//ACK
					send_msg.page 	= 0;
					for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
						send_msg.data[j] = 0;
					send_msg.size 	= 0;

					send_msg_from_eeprom(&send_msg);
					break;

				default:
					send_msg.PID 	= recv_msg.PID;
					send_msg.CMD_ID = EEPROM_CMD_NACK;	//ERROR
					send_msg.page 	= 0;
					for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
						send_msg.data[j] = 0;
					send_msg.size 	= 0;

					send_msg_from_eeprom(&send_msg);
					break;
			}
		}
		vTaskDelay(10);
	}
}

void lcd_update(void *p)
{
	char str[16];
	while(1)
	{
		lcd_clear();
		lcd_cursor(0, 0);
		lcd_send_string ("HORA:");
//		lcd_cursor(1, 0);
//		sprintf(str, "%d", (uint16_t) HAL_GetTick());
		lcd_send_string(str);

		vTaskDelay(1000);
	}
}


void actualizar_nivel_bateria(void *p)
{
//	struct eeprom_message send_msg;
//	struct eeprom_message recv_msg;
//	uint8_t status;
//	uint8_t space_available = 0;

	while(1)
	{
//		space_available = uxQueueSpacesAvailable(queue_to_eeprom);
//
//		if (space_available > 0)
//		{
//			send_msg.PID 	= PID_ADC;
//			send_msg.CMD_ID = EEPROM_CMD_READ;
//			send_msg.page 	= 3;
//			for (int j = 0; j < EEPROM_PAGE_SIZE; j++)
//				send_msg.data[j] = 0;
//			send_msg.size 	= EEPROM_PAGE_SIZE;
//			status = xQueueSend(queue_to_eeprom, &send_msg, EEPROM_MAX_QUEUE_DELAY);
//			if (status == errQUEUE_FULL){
//				Error_Handler();
//			}
//
//			do{
//				status = xQueuePeek(queue_from_eeprom, &recv_msg, EEPROM_MAX_QUEUE_DELAY);
//				if (status == pdTRUE){
//					if(recv_msg.PID == PID_ADC)
//					{
//						status = xQueueReceive(queue_from_eeprom, &recv_msg, EEPROM_MAX_QUEUE_DELAY);
//					}else{
//						status = pdFALSE;
//					}
//				}
//				vTaskDelay(10);
//			}while(status != pdTRUE);
//		}

		vTaskDelay(100);
	}
}

