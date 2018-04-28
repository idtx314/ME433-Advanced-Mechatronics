#include<xc.h>           // processor SFR definitions
#include<math.h>
#include<sys/attribs.h>  // __ISR macro
#include"i2clib.h"

/*Notes
 * SYSCLK = 48MHz
 * PBCLK = SYSCLK
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
void ms_wave(void);
void demo_wave(void);
void SPI1_init(void);
void i2c2_init(void);
void setVoltage(char channel, float voltage);
char SPI1_io(char msg);
double triangle_gen(double amplitude, double time, double wave_period);
double sin_gen(double amplitude, double time, double wave_period);

//Definitions
#define CS LATBbits.LATB15  //DAC Chip select shortcut. Expects 16 bit transmissions

typedef union {
  struct {
    unsigned int X:2;
    unsigned int VOLT:10;
    unsigned int SHDN:1;
    unsigned int GA:1;
    unsigned int BUF:1;
    unsigned int CHAN:1;
  };
  struct {
    unsigned int byte2:8;
    unsigned int byte1:8;
  };
  struct {
    unsigned int w:16;
  };
} __DAC_MSG_bits_t;

__DAC_MSG_bits_t DACMSGbits;


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
    SPI1_init();
    DACMSGbits.BUF = 0b1;
    DACMSGbits.GA = 0b1;
    DACMSGbits.SHDN = 0b1;
    DACMSGbits.X = 0b00;
    
    //Set up I2C
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    i2c_init_expander();
    
    __builtin_enable_interrupts();

    
    //register 0x09 is GPIO
    //read it to read
    //write it to have bits written to latch
    while(1) {
        _CP0_SET_COUNT(0);
        if((read_expander(0x09) & 0b10000000) == 0)
            set_expander(0x09, 0b00000001);  //LED on
        else
            set_expander(0x09, 0b00000000);  //LED off
        LATAINV = 1 << 4;
        while(_CP0_GET_COUNT() < 1200000)     //Wait 1/20 s
        {;}
    }


}


void setVoltage(char channel, float voltage){
    /*
     * Given a channel 'a' or 'b' and a voltage as a float, will set the 
     * appropriate channel on the DAC to output the given voltage.
     *
     * Transmission must consist of 16 bits. 
     * The first 4 are configuration bits for the device.
     * The following 10 are output setting bits, from most to least significant.
     * The last 2 are ignored.
     * Page 23 of Data sheet for details.
     */

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
    DACMSGbits.VOLT = 0b1111111111 & (int)(1023. * voltage / (3.3 * 1.));
    
    
    
    CS = 0;                         //Begin command
    SPI1_io(DACMSGbits.byte1);      //Though given as ints, these should be read as characters.
    SPI1_io(DACMSGbits.byte2);
    //TODO a pause here?
    CS = 1;                         //End command
}

char SPI1_io(char msg){
    /*
     * Send a byte and receive a byte, which is then returned.
     */
    SPI1BUF = msg;
    while(!SPI1STATbits.SPIRBF)
    {;}
    return SPI1BUF;
}

void SPI1_init(void) {
    /*
     * Sets up the SPI1 channel on the PIC
     */
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
    SPI1BRG = 0x1;          // Bit rate to 12 MHz, SPI1BRG = SysCLK/(2*desired)-1
    SPI1STATbits.SPIROV = 0;// clear the overflow
    SPI1CONbits.MSTEN = 1;  // master mode
    SPI1CONbits.CKE = 1;    // Change output data when clock goes from hi to low.
    SPI1CONbits.ON = 1;     // turn SPI on
    
}

void ms_wave(){
    while(1) {
    // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
    // remember the core timer runs at half the 48MHz sysclk, so 24MHz.
    // Should be able to see a waveform by measuring voltage across the user LED.
        while(!PORTBbits.RB4)
        {;}
        _CP0_SET_COUNT(0);
        setVoltage('a', 3); //VoutA to 3V
        LATAbits.LATA4 = 1; //Turn on LED
        while(_CP0_GET_COUNT() < 12000) //.5ms
        {;}
        setVoltage('a', 0); //VoutA to 0V
        LATAbits.LATA4 = 0; //Turn off LED
        while(_CP0_GET_COUNT() < 24000) //1ms
        {;}
    }
}

void demo_wave(){

    //Variables
    double t_wave_period = 1.0/5.0;             //Seconds per wave
    double t_duration = t_wave_period;                //Duration of the trajectory
    double s_wave_period = 1.0/10.0;            //Seconds per wave
    double s_duration = s_wave_period;                //Duration of the trajectory    
    double samp = 1000.;                //Samples per second
    double t_time = 0;                    //Time stamp
    double s_time = 0;
    int i;
    int j;



    double t_numsamps = samp * t_duration;  //Total Samples
    double s_numsamps = samp * s_duration;
    double t_pointarray[(int)t_numsamps];
    double t_timearray[(int)t_numsamps];
    double s_pointarray[(int)s_numsamps];
    double s_timearray[(int)s_numsamps];
    

    for(i=0; i<(int)t_numsamps; i++)
    {
        t_pointarray[i] = triangle_gen(3.3, t_time, t_wave_period);
        t_timearray[i] = t_time;
        t_time = t_time + 1.0/samp;          //Seconds per sample
    }
    for(j=0; j<(int)s_numsamps; j++)
    {
        s_pointarray[j] = sin_gen(1.65, s_time, s_wave_period);
        s_timearray[j] = s_time;
        s_time = s_time + 1.0/samp;          //Seconds per sample
    }
        

    i=j=0;
    int sample_period = (int)(1./samp * 1000. * 24000.);  //In s/sample * ms/s * ticks/ms
    
    while(1) {
    // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
    // remember the core timer runs at half the 48MHz sysclk, so 24MHz.
    // Should be able to see a waveform by measuring voltage across the user LED.        
        
        while(!PORTBbits.RB4)
        {;}
        
        _CP0_SET_COUNT(0);
        setVoltage('b', t_pointarray[i]); //VoutB to Triangle
        setVoltage('a', s_pointarray[j]); //VoutA to Sine
        i++;
        j++;
        if(i >= t_numsamps)
            i=0;
        if(j >= s_numsamps)
            j=0;
        LATAbits.LATA4 = 1; //Turn on LED
        while(_CP0_GET_COUNT() < sample_period/2) //.5ms
        {;}
        LATAbits.LATA4 = 0; //Turn off LED
        while(_CP0_GET_COUNT() < sample_period) //24,000 ticks, or 1 ms
        {;}
    }
}

double triangle_gen(double amplitude, double time, double wave_period){
    return (amplitude * 2/wave_period * (wave_period/2 - fabs(fmod(time, wave_period) - wave_period/2)));
}

double sin_gen(double amplitude, double time, double wave_period){
    float phase = 0.0;
    return amplitude * sin(2.0 * 3.14159 * 1.0/wave_period * time + phase) + 1.65;
}