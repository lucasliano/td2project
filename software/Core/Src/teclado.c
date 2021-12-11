/*
 * teclado.c
 *
 *  Created on: Sep 20, 2021
 *      Author: manuel
 */
#include "main.h"


/* ========= Variables Globales ==============*/
arrebote boton[4][4];
uint8_t clave[4];

/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_clave;

/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/

/* ===========================================*/

uint8_t chequear_clave(uint8_t *t){
	uint8_t out = 0;

	xSemaphoreTake(sem_clave,portMAX_DELAY);
	if (t[LARGO_CLAVE] == '#'){
		if (t[0]==clave[0] && t[1]==clave[1] && t[2]==clave[2] && t[3]==clave[3]){
			out = 1;
		}
		else
			out = 0;
	}
	else
		out = 0;
	xSemaphoreGive(sem_clave);
	return out;
}


void init_teclado(void){
	memcpy(clave, "1234", 4);
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
