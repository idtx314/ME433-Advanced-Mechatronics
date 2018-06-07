


// Includes
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro




// Prototypes





// Variables
    float l_d_vel=0, r_d_vel=0;     // Desired velocities




// Interrupt Service Routine
void __ISR(_TIMER_?_VECTOR, IPL5SOFT) Velocity_Control(void)
{
    // Local Variables
    static int l_prev_count;
    static float l_eint;


    // Get encoder count
    l_count = TMR?;

    // Calculate average wheel speed since last interrupt
    l_vel = (l_count - l_prev_count) / time period;

    // Perform PI control
        // Calculate error
        // Negative if velocity too high, positive if too low
    l_error = l_d_vel - l_vel;

        // Calculate integrated error
    l_eint += l_error;
            // Cap integrated error
    if(l_eint > max_e_cap)
        l_eint = max_e_cap;
    else if(l_eint < min_e_cap)
        l_eint = min_e_cap;

        // Calculated desired speed
    l_d_vel = l_Vp*l_error + l_Vi*l_eint;

        // Cap desired value to range
    if(l_d_vel > max_v_cap)
        l_d_vel = max_v_cap;
    else if (l_d_vel < min_v_cap)
        l_d_vel = min_v_cap;

    // Set PWM based on speed (sets duty cycle?)
        // Set DUTY
        // Set OC?RS = DUTY * (PR? +1)/100;




    // Clear Flag
}



int main()
{
    // Set Variables

    // Deactivate Interrupts
        // Initialize microcontroller (OC pins, AN pins, LED and button pins)

        // Configure communications

        // Configure timers

        // Init interrupts

        // Init encoders

        // Enable everything
    // Re-activate Interrupts


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



























