#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ST7735.h"          //LCD Library
#include<stdio.h>

/*Notes
 * SYSCLK = 48MHz
 * PBCLK = SYSCLK
 * Core clock = 24MHz
 * Expander Address = 0100 A2,A1,A0,R/W
 * R = 1, W = 0
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
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module


//Prototypes
void LCD_drawChar(unsigned short x, unsigned short y, char character, unsigned short c1, unsigned short c2);
void LCD_drawString(unsigned short x, unsigned short y, char* message, unsigned short c1, unsigned short c2);
void LCD_drawBar(unsigned short x, unsigned short y, unsigned short h, unsigned short len1, unsigned short c1, unsigned short len2, unsigned short c2);


//Definitions


/*TODO
 * Move heartbeat into being an interrupt
 * 
 */

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
    
    // do your TRIS and LAT commands here
    //Set up power LED and User button
    //ANSSELbits do not need to be cleared, these ports do not have analog functions
    TRISAbits.TRISA4 = 0;   //TRIS a4 to 0utput (pin 12) for LED
    LATAbits.LATA4 = 1;     //LAT a4 to 1
    TRISBbits.TRISB4 = 1;   //TRIS b4 to 1nput (pin 11) for button
    
    //Set up SPI1
    //Set up LCD
    LCD_init();
        
    LCD_clearScreen(BLACK);
    __builtin_enable_interrupts();

    
    char msg[30];
    int i=0;
    float fps=0;
    
    while(1){
        _CP0_SET_COUNT(0);
        if(!PORTBbits.RB4){
            sprintf(msg, "Hello World %d", i);
            LCD_drawString(10, 10, msg, WHITE, RED);
            LCD_drawBar(10, 20, 5, i, WHITE, 100-i, RED);
            i++;
            if (i>100)
                i=0;
            sprintf(msg, "FPS: %5.2f", 1.0/(_CP0_GET_COUNT()/48000000.0)); 
            LCD_drawString(10, 30, msg, WHITE,RED);
        }
        else {
            LCD_clearScreen(BLACK);
            i=0;
        }
        while(_CP0_GET_COUNT() < 2400000)     //Wait 1/10 s
        {;}
        //Do stuff, print stuff, wait
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
