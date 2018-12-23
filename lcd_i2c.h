#ifndef LCD_I2C_H_INCLUDED
#define	LCD_I2C_H_INCLUDED

#include <xc.h>

#define LCD_PRODUCT_AE_AQM1602A_3_3V 0x01
#define LCD_PRODUCT_AE_AQM1602A_5_0V 0x02

void lcd_i2c_write(unsigned char addr, unsigned char cont, char data);
void lcd_i2c_init(unsigned char addr, unsigned char product);
void lcd_i2c_print_char(unsigned char addr, char ch);
void lcd_i2c_print_str(unsigned char addr, const char * str);

#endif
