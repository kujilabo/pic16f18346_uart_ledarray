#include <xc.h>
#include "common.h"
#include "isr.h"
#include "i2c.h"
#include "lcd_i2c.h"
#include "version.h"
#include <string.h>

void send_text(const char *p){
    int count = strlen(p);
    for (int i = 0; i < count; i++) {
        while(TXIF ==  0) ;
        TXREG = *(p + i) ;
    }
}

int main() {
    unsigned char data[64 + 2];
    
    TRISA = 0x00;
    
    TRISBbits.TRISB4 = 1; // SDA
    TRISBbits.TRISB5 = 1; // SCL
    TRISBbits.TRISB6 = 0; // TX
    TRISBbits.TRISB7 = 1; // RX
    
    TRISC = 0x00;
    
    // I2C
    PMD4bits.MSSP2MD = 1;
    SSP1ADD = 0x27;
    SSP1DATPPS = 0b01100;
    SSP1DATPPS = 0b01100; // PPS INPUT RB4 = SDA1
    SSP1CLKPPS = 0b01101; // PPS INPUT RB5 = SCL1
    RB4PPS = 0b11001; // SDA
    RB5PPS = 0b11000; // SCL
    
    // UART
    RB6PPS = 0b10100; // TX
    RXPPS = 0b01111; // RB7
    
    TX1STAbits.TX9 = 0; // Selects 8-bit transmission
    TX1STAbits.TXEN = 1; // Transmit enabled
    TX1STAbits.BRGH = 0;
    RC1STA  = 0b10010000; // 
    SPBRG  = 25; // 19200bps
    
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;
    
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00;
    SSP1STAT = 0b10000000;
    
    T0CON0 = 0b10000000;
    T0CON1 = 0b01000100;
    TMR0H = 50;
    
    PORTA = 0x04;
    
    INTCONbits.PEIE = 1;
    PIE0bits.TMR0IE = 1;
    INTCONbits.GIE = 1;

    __delay_ms(100);

#ifdef USE_LCD
    lcd_i2c_init(LCD_I2C_ADDRESS, LCD_PRODUCT_AE_AQM1602A_3_3V);
    lcd_i2c_write(LCD_I2C_ADDRESS, 0x00, 0x80);
    lcd_i2c_print_str(LCD_I2C_ADDRESS, VERSION);
#endif

    send_text(VERSION);
    send_text("\n");

    while (1) {
        if (get_rx_flag() == 1) {
            unsigned char copy_size = get_rx_data(data, 64);
#ifdef USE_LCD
            data[copy_size] = '\0';
            lcd_i2c_write(LCD_I2C_ADDRESS, 0x00, 0x80);
            lcd_i2c_print_str(LCD_I2C_ADDRESS, data);
#endif

            data[copy_size] = '\n';
            data[copy_size + 1] = '\0';
            send_text(data);
        }
    }
    
    return 0;
}
