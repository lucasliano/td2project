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


//------------------- Eventos --------------------------------
#define EVENT_ALARM_ON			0
#define EVENT_ALARM_OFF			1
#define EVENT_POWER_ON			2
#define EVENT_POWER_OFF			3
#define EVENT_ALARM_BEEP_SALA1	4
#define EVENT_ALARM_BEEP_SALA2	5

//------------------- Estados -------------------------------
#define APAGADO				0
#define ENCENDIDIO			1
#define ALARMANDO			2


//------------------- Funciones ------------------------------
void checkear_teclado(void *p);
void detectar_rfid(void *p);
void detectar_sensores(void *p);
void conexion_bt(void *p);
void checkear_power_supply(void *p);
void lcd_update(void *p);
void actualizar_nivel_bateria(void *p);

#endif /* __TAREAS_H */
