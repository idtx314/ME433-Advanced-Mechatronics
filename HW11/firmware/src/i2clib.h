#ifndef I2CLIB_H__
#define I2CLIB_H__
// Header file for i2c_master_noint.c
// helps implement use I2C1 as a master without using interrupts

void i2c_master_setup(void);              // set up I2C 1 as a master, at 400 kHz
void i2c_init_expander(void);             // Set up the MCP23008 I/O port expander over I2C
void i2c_init_imu(void);
void i2c_read_imu(float * output);
void i2c_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length);
void imu_test();                          //Runs an algorithm that prints IMU data to the LCD
char read_expander(char reg);               //Read the values of an expander register
void set_expander(char reg, char bits);     //Set the expander register to the given bits

void i2c_master_start(void);              // send a START signal
void i2c_master_restart(void);            // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv(void);      // receive a byte of data
void i2c_master_ack(int val);             // send an ACK (0) or NACK (1)
void i2c_master_stop(void);               // send a stop

#endif
