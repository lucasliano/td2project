/*
 * lcd.h
 *
 *  Created on: Oct 25, 2021
 *      Author: lliano
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#define LCD_ADDRESS_I2C 0x4E

void lcd_init (I2C_HandleTypeDef *s);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_send_string (char *str, uint8_t size);
void lcd_cursor(int row, int col);
void lcd_clear (void);

#endif /* INC_LCD_H_ */
