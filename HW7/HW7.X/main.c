#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ST7735.h"          //LCD Library
#include<stdio.h>

/*Notes
 * SYSCLK = 48MHz
 * PBCLK = SYSCLK
 * Core clock = 24MHz
 * LCD 128x160
 *
 */

// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable secondary osc
#pragma config FPBDIV = DIV_1 // divide SYSCLK freq by 1 for PBCLK
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1048576 // use slowest wdt (largest ratio)
#pragma config WINDIS = OFF // wdt no window mode
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module


//Prototypes
void timer4_init();
void imu_test();

//Definitions
#define IMUADD 0b1101010

/*TODO
 * display data as bars
 * Add safety cutoff for drawBar
 *
 */

void __ISR(_TIMER_4_VECTOR, IPL5SOFT) Heartbeat(void) { //vector = 16


    //toggle light
    LATAINV = 1 << 4;

    //reset flag
    IFS0CLR = 1 << 19;
}

int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;
    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;
    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    //Configure timer 4
    timer4_init();

    // do your TRIS and LAT commands here
    //Set up power LED and User button
    //ANSSELbits do not need to be cleared, these ports do not have analog functions
    TRISAbits.TRISA4 = 0;   //TRIS a4 to 0utput (pin 12) for LED
    LATAbits.LATA4 = 1;     //LAT a4 to 1
    TRISBbits.TRISB4 = 1;   //TRIS b4 to 1nput (pin 11) for button

    //Set up SPI1
    //Set up LCD
    LCD_init();

    //Set up I2C
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    i2c_init_imu();

    LCD_clearScreen(BLACK);
    __builtin_enable_interrupts();

    while(1){
        _CP0_SET_COUNT(0);
        imu_test();
        while(_CP0_GET_COUNT() < 1200000)
        {;}
    }
}


void imu_test(){
    unsigned char data[14];
    short info[7];
    float output[7];
    char msg[30];
    int i;
    char whoami[1];
    float resolution[7] = {40, 1000, 1000, 1000, 2, 2, 2};
    short maxg = 0,ming = 0;

    //First IMU measure reg = 0x20
    //length = 14

    i2c_read_multiple(IMUADD, 0x0F, whoami, 1);

    sprintf(msg, "I am: %d",whoami[0]);
    LCD_drawString(10, 10, msg, WHITE, BLACK);

    
    i2c_read_multiple(IMUADD, 0x20, data, 14);

    for(i=0; i<7; i++){
        info[i] = (data[2*i+1])<<8 | (data[2*i]);
    }
    if(info[6] > maxg)
        maxg = info[6];
    if(info[6] < ming)
        ming = info[6];

    for(i=0; i<7; i++){
        output[i] = (float)info[i] / 32767. * resolution[i];
    }

    //4 = x, 5=y, 6=z 40-output[4]/2*40
    if(output[4]>0){
        LCD_drawBar(22, 78, 5, 40, RED, 0, WHITE);
        LCD_drawBar(67, 78, 5, output[4]/2*40, WHITE, 40, RED);
    }
    else if(output[4]<0){
        LCD_drawBar(67, 78, 5, 0, WHITE, 40, RED);
        LCD_drawBar(22, 78, 5, (unsigned short)(40+output[4]/2*40), RED, 40, WHITE);
    }
    if(output[5]>0){
        LCD_drawvBar(62, 38, 5, 40, RED, 0, WHITE);
        LCD_drawvBar(62, 83, 5, output[5]/2*40, WHITE, 40, RED);
    }
    else if(output[5]<0){
        LCD_drawvBar(62, 83, 5, 0, WHITE, 40, RED);
        LCD_drawvBar(62, 38, 5, 40+output[5]/2*40, RED, 40, WHITE);
    }


//    for(i=0; i<7; i++){
//        sprintf(msg, "Info %d: %7d",i, info[i]);
//        LCD_drawString(10, 10*i+30, msg, WHITE, BLACK);
//    }
//    sprintf(msg, "Maxg: %7d", maxg);
//    LCD_drawString(10, 100, msg, WHITE, BLACK);
//    sprintf(msg, "Ming: %7d", ming);
//    LCD_drawString(10, 110, msg, WHITE, BLACK);

}

void timer4_init(){

    T4CONbits.TCKPS = 0b111;//Prescaler 1:256 from SYSCLK
    TMR4 = 0;           //Reset count
    PR4 = 46875;        //Set Period for 4Hz

    IPC4bits.T4IP = 5;  //Priority 5
    IPC4bits.T4IS = 0;  //Sub-priority 0
    IFS0bits.T4IF = 0;  //Clear flag


    IEC0bits.T4IE = 1;  //Activate Interrupt
    T4CONbits.ON = 1;   //Activate Timer

}
