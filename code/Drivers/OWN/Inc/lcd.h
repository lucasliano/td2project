/*
 * lcd.h
 *
 *  Created on: Oct 25, 2021
 *      Author: lliano
 */

#ifndef OWN_INC_LCD_H_
#define OWN_INC_LCD_H_

#define LCD_ADDRESS_I2C 0x4E

void lcd_init (I2C_HandleTypeDef *s);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_send_string (char *str);
void lcd_cursor(int row, int col);
void lcd_clear (void);

#endif /* OWN_INC_LCD_H_ */
