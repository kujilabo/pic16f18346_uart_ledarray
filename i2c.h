#ifndef I2C_H_INCLUDED
#define	I2C_H_INCLUDED

#include <xc.h>

void i2c_start();
void i2c_stop();
void i2c_wait();
void i2c_write_data(unsigned char data);

#endif
