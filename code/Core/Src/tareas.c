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

/* ---------  Variables de estado ------------*/
extern arrebote boton[4][4];
extern uint8_t clave_ok;
/* ===========================================*/

void checkear_teclado(void *p)
{
	/*
	 * ======== checkear_teclado =============
	 * Tarea global.
	 *
	 *
	 * -------- Uso de memoria -------------
	 * Stack size:
	 * 				uint8_t i   		-> 8 bytes
	 * 				uint8_t cardstr[5]  -> 8*5 = 40 bytes
	 * 				uint8_t estado      -> 8 bytes
	 * 				========================================
	 * Total:							-> 56 bytes
	 */
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
	uint8_t estado=0;

	for(;;){
		switch(estado){
		case 0:				//APAGADO
			xSemaphoreTake(sem_clave,portMAX_DELAY);
							if(clave_ok){
								estado=1;
								clave_ok = 0; //Bajo el flag
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
							}
			xSemaphoreGive(sem_clave);
			break;

		}
		vTaskDelay(DEMORA_SENSOR / portTICK_RATE_MS);
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

