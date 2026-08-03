#ifndef I2C_H_
#define I2C_H_

#include "stm32f411xe.h"

void i2c1_init();
void i2c1_read(char saddr, char maddr, unsigned int n, char *data);
void i2c1_write(char saddr, char maddr, unsigned int n, char *data);

void i2c2_init();
void i2c2_read(char saddr, char maddr, unsigned int n, char *data);
void i2c2_write(char saddr, char maddr, unsigned int n, char *data);
#endif // I2C_H_