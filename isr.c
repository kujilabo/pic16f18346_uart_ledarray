#include "isr.h"
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#define RX_SIZE 64

static char rx_data[RX_SIZE];
static char led[10];
static char rx_flag;
static unsigned char rx_size;
static char rx_index = 0;
static char rx_comment = 0;
static char rx_protocol;

unsigned char get_rx_data(char * data, unsigned char size) {
    PIE1bits.RCIE = 0;
    unsigned char copy_size = min(size, rx_index);
    memcpy(data, rx_data, copy_size);
    rx_flag = 0;
    rx_index = 0;
    PIE1bits.RCIE = 1;
    return copy_size;
}

char get_rx_flag() {
    char tmp;
    PIE1bits.RCIE = 0;
    tmp = rx_flag;
    PIE1bits.RCIE = 1;
    return tmp;
}

static void timer0() {
    PORTA = (led[0] << 5) |
            (led[1] << 4);
    PORTC = (led[2] << 5) | 
            (led[3] << 4) | 
            (led[4] << 3) | 
            (led[5] << 6) |
            (led[6] << 7) |
            (led[7] << 2) |
            (led[8] << 1) |
            (led[9]);
}

static void process() {
    for (int i = 0; i < 10; i++) {
        led[i] = (rx_data[i + 4] == '1') ? 1 : 0;     
    }
    rx_flag = 1;
}

static void rc() {
    while (PIR1bits.RCIF) {
        unsigned char tmp = RCREG;
        
        if (rx_flag == 1) {
            break;
        } else if (rx_index == RX_SIZE) {
            rx_index = 0;
            break;
        } else if (tmp == '\n' || tmp == '\r') {
            if (rx_index == rx_size + 4) {
                process();
            }
            
            rx_flag = 1;
            rx_comment = 0;
            break;
        }
              
        rx_data[rx_index] = tmp;      
        
        if (rx_comment == 0) {   
            if (rx_index == 0) {
                if (tmp == '-') {
                    rx_comment = 1;
                }
            } else if (rx_index == 1) {
                rx_protocol = tmp;
            } else if (rx_index == 2) {
            } else if (rx_index == 3) {
                rx_size = 10;
            }
        }
               
        rx_index++;
    }
}


void interrupt isr(void) {
    if (PIR0bits.TMR0IF) {
        timer0();
        PIR0bits.TMR0IF = 0;
    }
    
    if (PIR1bits.RCIF) {
        rc();
        PIR1bits.RCIF = 0;
    }
}

// 010A1000000000
// 010A0100000000
// 010A0010000000
// 010A0001000000
// 010A0000100000
// 010A0000010000
// 010A0000001000
// 010A0000000100
// 010A0000000010
// 010A0000000001
// 010A1111111111
