/**
  ******************************************************************************
  * @file           : tareas.h
  * @brief          : Definición de las tareas.
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TAREAS_H
#define __TAREAS_H
#include <semphr.h>  //Esto porque sino no me tomaba SemaphoreHandle_t


void checkear_teclado(void *p);
void detectar_rfid(void *p);
void detectar_sensores(void *p);
void conexion_bt(void *p);
void checkear_power_supply(void *p);
void manejo_eeprom(void *p);
void lcd_update(void *p);
//void actualizar_nivel_bateria(void *p);

#endif /* __TAREAS_H */
