#ifndef __I2C_H__
#define __I2C_H__


void i2c_init(void);
void i2c_start(void);
void i2c_stop (void);
void i2c_wb (unsigned char val);
unsigned char i2c_rb (unsigned char ack);


#endif // __I2C_H__
