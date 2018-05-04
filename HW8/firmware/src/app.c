/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ST7735.h"          //LCD Library
#include<stdio.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
//Definitions
#define IMUADD 0b1101010

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/
void LCD_drawChar(unsigned short x, unsigned short y, char character, unsigned short c1, unsigned short c2);
void LCD_drawString(unsigned short x, unsigned short y, char* message, unsigned short c1, unsigned short c2);
void LCD_drawBar(unsigned short x, unsigned short y, unsigned short h, unsigned short len1, unsigned short c1, unsigned short len2, unsigned short c2);
void LCD_drawvBar(unsigned short x, unsigned short y, unsigned short h, unsigned short len1, unsigned short c1, unsigned short len2, unsigned short c2);
void timer4_init();
void LCD_test();


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    //Set up power LED and User button
    //ANSSELbits do not need to be cleared, these ports do not have analog functions
    TRISAbits.TRISA4 = 0;   //TRIS a4 to 0 (pin 12) for LED
    LATAbits.LATA4 = 1;     //LAT a4 to 1
    TRISBbits.TRISB4 = 1;   //TRIS b4 to 1 (pin 11) for button

    //Set up SPI1
    //Set up LCD
    LCD_init();
    
    //Set up I2C
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    i2c_init_imu();
        
    LCD_clearScreen(BLACK);
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    static unsigned char data[14];
    static short info[7];
    static float output[7];
    static char msg[30];
    static int i;
    static char whoami[1];
    static float resolution[7] = {40, 1000, 1000, 1000, 2, 2, 2};
    static short maxg = 0,ming = 0;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;


            //First IMU measure reg = 0x20
            //length = 14

            i2c_read_multiple(IMUADD, 0x0F, whoami, 1);

            sprintf(msg, "I am: %d",whoami[0]);
            LCD_drawString(10, 10, msg, WHITE, BLACK);
            
            if (appInitialized)
            {
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
            // remember the core timer runs at half the 48MHz sysclk, so 24MHz.
            // Should be able to see a waveform by measuring voltage across the user LED.
            _CP0_SET_COUNT(0);
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


            //        for(i=0; i<7; i++){
            //            sprintf(msg, "Info %d: %7d",i, info[i]);
            //            LCD_drawString(10, 10*i+30, msg, WHITE, BLACK);
            //        }
            //        sprintf(msg, "Maxg: %7d", maxg);
            //        LCD_drawString(10, 100, msg, WHITE, BLACK);
            //        sprintf(msg, "Ming: %7d", ming);
            //        LCD_drawString(10, 110, msg, WHITE, BLACK);
            
            
            LATAINV = 1<<4;
            while(_CP0_GET_COUNT() < 1200000)
            {;}
        
            break;
        }


        
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
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

void LCD_test() {
    char msg[30];
    int i=0;
    
    while(1){
        _CP0_SET_COUNT(0);
        if(!PORTBbits.RB4){
            sprintf(msg, "Hello World %3d", i);
            LCD_drawString(10, 10, msg, WHITE, RED);
            LCD_drawvBar(10, 20, 5, i, WHITE, 100-i, RED);
            i++;
            if (i>100) {
                i=0;
//                sprintf(msg, "                         ");
//                LCD_drawString(0, 10, msg, WHITE, BLACK);
            }
            sprintf(msg, "FPS: %5.2f", 1.0/(_CP0_GET_COUNT()/48000000.0)); 
            LCD_drawString(10, 30, msg, WHITE,RED);
        }
        else {
            LCD_clearScreen(BLACK);
            i=0;
        }
        while(_CP0_GET_COUNT() < 2400000)     //Wait 1/10 s
        {;}
    }
}

void LCD_drawBar(unsigned short x, unsigned short y, unsigned short h, unsigned short len1, unsigned short c1, unsigned short len2, unsigned short c2){
    int i, j;
    
    for (j=0; j<h; j++) {
        for (i=0; i<len1; i++) {
            LCD_drawPixel(x+i, y+j, c1);
        }
        for (i=len1; i<len2; i++) {
            LCD_drawPixel(x+i, y+j, c2);
        }
    }
    
}
void LCD_drawvBar(unsigned short x, unsigned short y, unsigned short h, unsigned short len1, unsigned short c1, unsigned short len2, unsigned short c2){
    int i, j;
    
    for (j=0; j<h; j++) {
        for (i=0; i<len1; i++) {
            LCD_drawPixel(x+j, y+i, c1);
        }
        for (i=len1; i<len2; i++) {
            LCD_drawPixel(x+j, y+i, c2);
        }
    }
    
}

void LCD_drawString(unsigned short x, unsigned short y, char* message, unsigned short c1, unsigned short c2){
    
    short index = 0;
    
    while(message[index]){
        LCD_drawChar(x, y, message[index], c1, c2);
        x = x+5;
        index++;
    }
}

void LCD_drawChar(unsigned short x, unsigned short y, char character, unsigned short c1, unsigned short c2) {
    //Model call LCD_drawChar(50, 50, 'H');
    //8 rows, 5 column
    
    int column=0, row=0;
    //get character from lookup table: an array of 5 chars
    
    for (column=0; column<5; column++){
        if(x+column >= 128)
            break;
        char pixels = ASCII[character-0x20][column];
        
        //mask bits one at a time and print them
        for (row=7; row> -1; row--){
            if(y+row >= 160)
                break;
            if((pixels >> row) & 1 == 1){
                LCD_drawPixel(x+column, y+row, c1);            
            }
            else {
                LCD_drawPixel(x+column, y+row, c2);
            }
        }
    }
}


/*******************************************************************************
 End of File
 */
