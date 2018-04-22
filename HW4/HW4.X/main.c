#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

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
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
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
void ms_wave(void);
void SPI1_init(void);
void setVoltage(char channel, int voltage);
char SPI1_io(char msg);

//Definitions
#define CS LATBbits.LATB15  //DAC Chip select shortcut. Expects 16 bit transmissions

typedef union {
  struct {
    uint16_t CHAN:1;
    uint16_t BUF:1;
    uint16_t GA:1;
    uint16_t SHDN:1;
    uint16_t VOLT:10;
    uint16_t :1;
    uint16_t :1;
  };
  struct {
    uint16_t byte1:8;
    uint16_t byte2:8;
  };
  struct {
    uint16_t w:16;
  };
} __DAC_MSG_bits_t;

__DAC_MSG_bits_t DACMSGbits;

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
    SPI1_init();
    DACMSGbits.BUF = 0;
    DACMSGbits.GA = 1;
    DACMSGbits.SHDN = 1;
    
    __builtin_enable_interrupts();

    
    ms_wave();


}


void setVoltage(char channel, int voltage)
{
    //Transmission must consist of 16 bits. 
    //The first 4 are configuration bits for the device.
    //The following 10 are output setting bits, from most to least significant.
    //The last 2 are ignored.
    //Page 23 of Data sheet for details.

    if(channel == 'a' || channel == 'A')
    {
        DACMSGbits.CHAN = 0b0;
    }
    else if(channel == 'b' || channel == 'B')
    {
        DACMSGbits.CHAN = 0b1;
    }
    //TODO error handling for non channel values and voltage overflow
    //TODO mechanism to shut channel down entirely if voltage set to 0 (or -1?)
    
    //Voltage Formula: Vout = voltage = (Vref*Dn)/2^n * G
    //                  Dn = 2^n * voltage / (Vref * G)
    DACMSGbits.VOLT = 1024 * voltage / (3.3 * 1);
    
    
    
    CS = 0;                         //Begin command
    SPI1_io(DACMSGbits.byte1);      //Though given as ints, these will be read as characters.
    SPI1_io(DACMSGbits.byte2);
    CS = 1;                         //End command
}

char SPI1_io(char msg)
{
    //Send a byte and receive a byte, which is then returned.
    SPI1BUF = msg;
    while(!SPI1STATbits.SPIRBF)
    {;}
    return SPI1BUF;
}

void SPI1_init(void) 
{
    //Some Registers of Note
    //SPIxSTATbits.SPITXBF  //Set when SPIxBUF has outgoing data in it.
    //SPIxSTATbits.SPIRXBF  //Set when SPIxBUF has incoming data in it.
    //SPIxBUF               //Use to read and write data.
    //SPIxCONbits.DISSDI    //Disable SDIx pin, free pin for PORT to control.
    //SPIxCONbits.CKP       //Configure clock active hi or active low.
    //SPIxCONbits.CKE       //Configure whether output changes on rising or falling edge.
    
    
    //Chip select configuration
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;     //Low to start command, high to end command
    
    //Reprogrammable Pin Setup
    RPB8Rbits.RPB8R = 0b0011;   //SDO1 on B8
    SDI1Rbits.SDI1R = 0b0000;   //SDI1 on A1

            
    // SPI initialization for talking to DAC chip
    SPI1CON = 0;            // stop and reset SPI4
    SPI1BUF;                // read to clear the rx receive buffer
    SPI1BRG = 0x1;          // bit rate to 12 MHz, SPI4BRG = 48000000/(2*desired)-1
    SPI1STATbits.SPIROV = 0;// clear the overflow
    SPI1CONbits.MSTEN = 1;  // master mode
    SPI1CONbits.CKE = 1;    // Change output data when clock goes from hi to low.
    SPI1CONbits.ON = 1;     // turn SPI on
    
}


void ms_wave()
{
    while(1) {
    // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
    // remember the core timer runs at half the 48MHz sysclk, so 24MHz.
    // Should be able to see a waveform by measuring voltage across the user LED.
        while(!PORTBbits.RB4)
        {;}
        _CP0_SET_COUNT(0);
        setVoltage(0, 3); //Turn on LED
        while(_CP0_GET_COUNT() < 12000) //.5ms
        {;}
        LATAbits.LATA4 = 0; //Turn off LED
        while(_CP0_GET_COUNT() < 24000) //1ms
        {;}
    }
}