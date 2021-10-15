/*
 * teclado.c
 *
 *  Created on: Sep 20, 2021
 *      Author: manuel
 */
#include "main.h"

arrebote boton[4][4];


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
