/**
  ******************************************************************************
  * @file           : tareas.c
  * @brief          : Archivo donde se programan las tareas a nivel de aplicación
  ******************************************************************************
**/

void checkear_teclado(void *p)
{

}

void detectar_rfid(void *p)
{

}

void detectar_sensores(void *p)
{
	// (Dependiendo del estado de la alarma, debe hacer sonar el buzzer)
}

void conexion_bt(void *p)
{
	// Maquinas de estados con ESPERANDO_CONEXION - ESPERANDO_COMANDO - ACTUANDO
}

void checkear_power_supply(void *p)
{
	// Lectura ADC
}

void escritura_eeprom(void *p)
{
	// Cola de mensajes
//	xQueueReceive(cola_tiempo, &item, portMAX_DELAY);
//	vTaskDelay(item);
//	xQueueSend(cola_todo_piola,&ok,portMAX_DELAY);
}

void lcd_update(void *p)
{

}

//void lectura_eeprom(void *p)
//{
//
//}

//void actualizar_nivel_bateria(void *p)
//{
//
//}

