#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINT32
#pragma config CLKOUTEN = OFF
#pragma config CSWEN = ON
#pragma config FCMEN = OFF
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#define _XTAL_FREQ 32000000

#define LCD_I2C_ADDRESS 0x7C

#define USE_LCD

#endif

