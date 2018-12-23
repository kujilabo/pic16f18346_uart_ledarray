#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "i2c.h"
#include "common.h"

void i2c_start() {
    SSP1CON2bits.SEN = 1;
    i2c_wait();
}

void i2c_stop() {
    SSP1CON2bits.PEN = 1;
    i2c_wait();
}

void i2c_wait() {
    while ((SSP1CON2 & 0x1F) || (SSP1STATbits.R_nW));
}

void i2c_write_data(unsigned char data) {
    SSP1BUF = data;
    i2c_wait();
}
