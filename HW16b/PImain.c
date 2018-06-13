


// Includes
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

// Constants
#define MAX_PWM 100
#define MIN_PWM 0
#define MAX_E_CAP
#define MIN_E_CAP
#define L_KP
#define R_KP
#define L_KI
#define R_KI


// Prototypes





// Variables
int l_d_vel=0, r_d_vel=0;     // Desired velocities


/* TODO
    Add the right wheel to ISR
    Get interrupt function into system_interrupt.c (in Source Files -> app -> system_config -> default -> framework)
*/



// Interrupt Service Routine
void __ISR(_TIMER_4_VECTOR, IPL4SOFT) Timer4ISR(void)
{
    // Local Variables
    static int l_prev_count, l_eint;
    int l_count, l_vel, l_error, l_d_pwm


    // Get encoder count?
    l_count = TMR?;

    // Calculate average wheel speed since last interrupt
    l_vel = (l_count - l_prev_count) / time period?; //Multiply by large number instead of dividing by small


    // Perform PI control
        // Calculate error
        // Negative if velocity too high, positive if too low
    l_error = l_d_vel - l_vel;

        // Calculate integrated error
    l_eint += l_error;
            // Cap integrated error
    if(l_eint > MAX_E_CAP)
        l_eint = MAX_E_CAP;
    else if(l_eint < MIN_E_CAP)
        l_eint = MIN_E_CAP;

        // Calculate desired PWM
    l_d_pwm = L_KP *l_error + L_KI *l_eint;

        // Cap desired value to range
    if(l_d_pwm > MAX_PWM)
        l_d_pwm = MAX_PWM;
    else if (l_d_pwm < MIN_PWM)
        l_d_pwm = MIN_PWM;

    // Set duty cycle based on controller output
        // Set OCxRS = Duty% * (PRx +1)/100;
    OC1RS = l_d_pwm * (PR2 + 1) /100;



    // Save the new counts
    l_prev_count = l_count;

    // Clear Flag
    IFS0bits.T4IF = 0;
}



int main()
{
    // Set Variables

    // Deactivate Interrupts
    __builtin_disable_interrupts();
        // Initialize microcontroller (OC pins, AN pins, LED and button pins)
    // Init OC pins
    // OC1 for left wheel, OC4 for right wheel
    RPA0Rbits.RPA0R = 0b0101; // A0 to OC1
    RPB13Rbits.RPB13R = 0b0101; // B13 to OC4
    OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OCxCON bits are defaults
    OC1RS = 0; // duty cycle
    OC1R = 0; // initialize before turning OC1 on; afterward it is read-only
    OC4CONbits.OCM = 0b110; // PWM mode without fault pin; other OCxCON bits are defaults
    OC4RS = 0; // duty cycle
    OC4R = 0; // initialize before turning OC4 on; afterward it is read-only

        // Configure communications

    // Configure timers
    // Timer 2 for PWM base frequency
    T2CONbits.TCKPS = 0; // Timer2 prescaler N=1 (1:1)
    PR2 = 2399; // 48000000 Hz / 20000 Hz / 1 - 1 = 2399 (20kHz PWM from 48MHz clock with 1:1 prescaler)
    TMR2 = 0; // initial TMR2 count is 0

    // Timer 5 for left encoder, Timer 3 for right encoder
    T5CKbits.T5CKR = 0b0100; // B9 is read by T5CK
    T5CONbits.TCS = 1; // count external pulses
    PR5 = 0xFFFF; // enable counting to max value of 2^16 - 1
    TMR5 = 0; // set the timer count to zero
    T3CKbits.T3CKR = 0b0100; // B8 is read by T3CK
    T3CONbits.TCS = 1; // count external pulses
    PR3 = 0xFFFF; // enable counting to max value of 2^16 - 1
    TMR3 = 0; // set the timer count to zero

    // Timer 4 for the controller interrupt
    T4CONbits.TCKPS = 2; // Timer4 prescaler N=4
    PR4 = 23999; // 48000000 Hz / 500 Hz / 4 - 1 = 23999 (500Hz from 48MHz clock with 4:1 prescaler)
    TMR4 = 0; // initial TMR4 count is 0

        // Init interrupts
    IPC4bits.T4IP = 4; // priority for Timer 4
    IFS0bits.T4IF = 0; // clear interrupt flag for Timer4

        // Init encoders

        // Enable everything
    T2CONbits.ON = 1; // turn on Timer2
    T3CONbits.ON = 1; // turn Timer on and start counting
    T5CONbits.ON = 1; // turn Timer on and start counting
    T4CONbits.ON = 1;
    OC1CONbits.ON = 1; // turn on OC1
    OC4CONbits.ON = 1; // turn on OC4
    IEC0bits.T4IE = 1; // enable interrupt for Timer4

    // Re-activate Interrupts
    __builtin_enable_interrupts();


    while(1)
    {
        // Receive camera position data

        // Interpret position data

        // Disable interrupts
            // Set desired PWM for each wheel based on data
        // Enable interrupts

    }

    return 0
}



























