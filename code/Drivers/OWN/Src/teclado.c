/*
 * teclado.c
 *
 *  Created on: Sep 20, 2021
 *      Author: manuel
 */
#include "teclado.h"
#include "arrebote.h"
#include "tareas.h"

arrebote boton[4][4];
extern xSemaphoreHandle sem_clave;
extern uint8_t clave_ok;

void tarea_teclado(void *p){
	uint8_t tecla[LARGO_CLAVE+1] = {0}; //Cuento el # de cierre
	uint8_t i=0;

	uint8_t estado = 0;

	for(;;){

		//Chequeo si esta la clave y todo OK
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


uint8_t chequear_clave(uint8_t *t){
	if (t[LARGO_CLAVE] == '#'){
		if (t[0]==CLAVE1 && t[1]==CLAVE2 && t[2]==CLAVE3 && t[3]==CLAVE4){
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}


void init_teclado(void){
	//Fila 1
	inicializar_arrebote(&boton[0][0],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[0][1],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[0][2],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[0][3],0,DEMORA_REBOTE/DEMORA_LECTURA);

	//Fila 2
	inicializar_arrebote(&boton[1][0],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[1][1],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[1][2],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[1][3],0,DEMORA_REBOTE/DEMORA_LECTURA);

	//Fila 3
	inicializar_arrebote(&boton[2][0],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[2][1],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[2][2],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[2][3],0,DEMORA_REBOTE/DEMORA_LECTURA);

	//Fila 4
	inicializar_arrebote(&boton[3][0],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[3][1],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[3][2],0,DEMORA_REBOTE/DEMORA_LECTURA);
	inicializar_arrebote(&boton[3][3],0,DEMORA_REBOTE/DEMORA_LECTURA);

}
