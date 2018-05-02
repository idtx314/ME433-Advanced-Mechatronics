#include<xc.h>
#include "i2clib.h"

/* I2C Master utilities, 400 kHz, using polling rather than interrupts
 * The functions must be callled in the correct order as per the I2C protocol
 * Change I2C2 to the I2C channel you are using
 * I2C pins need pull-up resistors, 2k-10k
 * Expander Address = 0100 A2,A1,A0,R/W
 * For writing I2C expander registers Read = 1, Write = 0
 * 
 * imu address: 0b 0110 101x, x=pin SD0
 * Read = 1, Write = 0
 */

#define EXPADD 0b0100000
#define IMUADD 0b1101010

/* TODO
 * Change i2c_init_imu to use sequential write
 */

char read_expander(char reg){
    /*
     * Given a register, returns the byte in that register
     */
    
    char r;
    
    i2c_master_start();
    i2c_master_send(0b01000000);    //OpcodeW
    i2c_master_send(reg);           //Register
    i2c_master_restart();           //Restart
    i2c_master_send(0b01000001);    //OpcodeR
    r = i2c_master_recv();          //Read
    i2c_master_ack(1);              //Acknowledge, Ending Read
    i2c_master_stop();              //Stop
    
    return r;
}

void set_expander(char reg, char bits){
    /*
     * Given an address for the register and the byte to write,
     * writes the byte to the register on the port expander.
     */
    
    i2c_master_start();
    i2c_master_send(0b01000000);    //OpcodeW
    i2c_master_send(reg);           //Register
    i2c_master_send(bits);          //Settings
    i2c_master_stop();              //Stop   
}

void i2c_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length){
    /*
     * Inputs:
     * address, the device address
     * reg, the register to start reading from
     * data, a pointer to a data storage array of chars
     * length, the size of the storage array
     */
    int i;
//    OpcodeW = (address<<1) | 0;
//    OpcodeR = (address<<1) | 1;
    
    i2c_master_start();
    i2c_master_send(0b11010100);    //OpcodeW
    i2c_master_send(reg);           //Register
    i2c_master_restart();           //Restart
    i2c_master_send(0b11010101);    //OpcodeR
    
    for(i=0; i<length-1; i++){      //From first to second to last read
        data[i] = i2c_master_recv();
        i2c_master_ack(0);
    }
    data[i] = i2c_master_recv();    //Last read
    i2c_master_ack(1);              //Acknowledge, Ending Read
    i2c_master_stop();              //Stop
    
}

void i2c_init_imu(void){
    //Accelerometer sample rate to 1.66KHz, +-2g range, 100Hz filter
    i2c_master_start();             //Start
    i2c_master_send(0b11010100);    //OpcodeW
    i2c_master_send(0b00010000);    //Register
    i2c_master_send(0b10000010);    //Settings
    i2c_master_stop();              //Stop
    
    //Gyroscope sample rate 10 1.66KHz, +-1000dps range
    i2c_master_start();             //Start
    i2c_master_send(0b11010100);    //OpcodeW
    i2c_master_send(0b00010001);    //Register
    i2c_master_send(0b10001000);    //Settings
    i2c_master_stop();              //Stop
}

void i2c_init_expander(void){
    //Activate Pullup Resistors
    i2c_master_start();             //Start
    i2c_master_send(0b01000000);    //OpcodeW
    i2c_master_send(0b00000110);    //Register
    i2c_master_send(0b11110000);    //Settings
    i2c_master_stop();              //Stop
    
    //Set Outputs to 1
    i2c_master_start();             //Start
    i2c_master_send(0b01000000);    //OpcodeW
    i2c_master_send(0b00001001);    //Register
    i2c_master_send(0b00001111);    //Settings
    i2c_master_stop();              //Stop

    //Set I/O
    i2c_master_start();             //Start
    i2c_master_send(0b01000000);    //OpcodeW
    i2c_master_send(0b00000000);    //Register
    i2c_master_send(0b11110000);    //Settings
    i2c_master_stop();              //Stop
}

void i2c_master_setup(void) {
  I2C2BRG = 53;            // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2
                                    // look up PGD for your PIC32
  I2C2CONbits.ON = 1;               // turn on the I2C2 module
}

void i2c_master_start(void) {
    I2C2CONbits.SEN = 1;            // send the start bit
    while(I2C2CONbits.SEN) { ; }    // wait for the start bit to be sent
}

void i2c_master_restart(void) {
    I2C2CONbits.RSEN = 1;           // send a restart
    while(I2C2CONbits.RSEN) { ; }   // wait for the restart to clear
}

void i2c_master_send(unsigned char byte) { // send a byte to slave
  I2C2TRN = byte;                   // if an address, bit 0 = 0 for write, 1 for read
  while(I2C2STATbits.TRSTAT) { ; }  // wait for the transmission to finish
  if(I2C2STATbits.ACKSTAT) {        // if this is high, slave has not acknowledged
    // ("I2C2 Master: failed to receive ACK\r\n");
  }
}

unsigned char i2c_master_recv(void) { // receive a byte from the slave
    I2C2CONbits.RCEN = 1;             // start receiving data
    while(!I2C2STATbits.RBF) { ; }    // wait to receive the data
    return I2C2RCV;                   // read and return the data
}

void i2c_master_ack(int val) {        // sends ACK = 0 (slave should send another byte)
                                      // or NACK = 1 (no more bytes requested from slave)
    I2C2CONbits.ACKDT = val;          // store ACK/NACK in ACKDT
    I2C2CONbits.ACKEN = 1;            // send ACKDT
    while(I2C2CONbits.ACKEN) { ; }    // wait for ACK/NACK to be sent
}

void i2c_master_stop(void) {          // send a STOP:
  I2C2CONbits.PEN = 1;                // comm is complete and master relinquishes bus
  while(I2C2CONbits.PEN) { ; }        // wait for STOP to complete
}
