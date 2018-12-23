#include <xc.h>
#include "common.h"
#include "i2c.h"
#include "lcd_i2c.h"

void lcd_i2c_write(unsigned char addr, unsigned char cont, char data) {
    i2c_start();
    i2c_write_data(addr);
    i2c_write_data(cont);
    i2c_write_data(data);
    SSP1IF = 0;
    i2c_stop();
    __delay_us(50);
}

void lcd_i2c_init(unsigned char addr, unsigned char product) {
    lcd_i2c_write(addr, 0x00, 0x38);
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x39);
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x14);
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x73);
    __delay_ms(20);
    if (product == LCD_PRODUCT_AE_AQM1602A_3_3V) {
        lcd_i2c_write(addr, 0x00, 0x56);
    } else if (product == LCD_PRODUCT_AE_AQM1602A_5_0V) {
        lcd_i2c_write(addr, 0x00, 0x52);
    } else {
        lcd_i2c_write(addr, 0x00, 0x56);
    }
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x6C);
    __delay_ms(300);
    lcd_i2c_write(addr, 0x00, 0x38);
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x01);
    __delay_ms(20);
    lcd_i2c_write(addr, 0x00, 0x0C);
    __delay_ms(20);
    
    
//    lcd_i2c_write(addr, 0x01, 0x30);
//    __delay_ms(20);
//    lcd_i2c_write(addr, 0x01, 0x30);
//    __delay_ms(20);
//    lcd_i2c_write(addr, 0x01, 0x30);
//    __delay_ms(20);
//    lcd_i2c_write(addr, 0x01, 0x20);
//    __delay_ms(20);    
//    lcd_i2c_write(addr, 0x00, 0x2E);
//    __delay_ms(20);
//    lcd_i2c_write(addr, 0x00, 0x08);
//    __delay_ms(300);
//    lcd_i2c_write(addr, 0x00, 0x0E);
//    __delay_ms(20);
//    lcd_i2c_write(addr, 0x00, 0x06);
//    __delay_ms(20);
}

void lcd_i2c_print_char(unsigned char addr, char ch) {
    lcd_i2c_write(addr, 0x40, ch);
//    lcd_i2c_write(addr, 0x80, ch);
    __delay_us(50);   
}

void lcd_i2c_print_str(unsigned char addr, const char * str) {
    while (*str) {
        lcd_i2c_print_char(addr, *str++);
    }    
}
