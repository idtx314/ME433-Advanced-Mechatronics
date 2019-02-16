/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

// Constants
#define MAX_PWM 100
#define MIN_PWM 0
#define MAX_E_CAP 500
#define MIN_E_CAP -500
#define L_KP 1.
#define R_KP 1.
#define L_KI 0.1
#define R_KI 0.05

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

 
void __ISR(_USB_1_VECTOR, ipl4AUTO) _IntHandlerUSBInstance0(void)
{
    DRV_USBFS_Tasks_ISR(sysObj.drvUSBObject);
}

void __ISR(_TIMER_4_VECTOR, IPL4SOFT) Timer4ISR(void){  //Runs at 500Hz
    // Local Variables
    static int l_prev_count = 0, r_prev_count = 0;
    static int l_eint = 0, r_eint=0;
    int l_count, r_count, l_vel, r_vel, l_error, r_error, l_d_pwm, r_d_pwm, l_vel_sum=0, r_vel_sum=0;
    int i;
    double l_avg, r_avg;


    // Get encoder count
    l_count = TMR5;
    r_count = TMR3;
    
    // Calculate average wheel speed since last interrupt
    // Multiply by large number instead of dividing by small
    // Measuring frequency is fast enough that rotation is often too slow to register, leading to extreme value changes
    l_vel = (l_count - l_prev_count) * 500;
    r_vel = (r_count - r_prev_count) * 500;
    
    // Update velocity histories
    // Oldest reading first
    for(i=0; i < (10-1); i++)
    {
        _l_velocity_history[i] = _l_velocity_history[i+1];
        _r_velocity_history[i] = _r_velocity_history[i+1];
    }
    _l_velocity_history[9] = l_vel;
    _r_velocity_history[9] = r_vel;
    
    // Use the last ten velocities to perform a moving average and compensate for the extreme value changes
    for(i=0; i < 10; i++)
    {
        l_vel_sum = l_vel_sum + _l_velocity_history[i];
        r_vel_sum = r_vel_sum + _r_velocity_history[i];
    }
    
    // TODO should I be using a double here?
    l_avg = l_vel_sum/10.0;
    r_avg = r_vel_sum/10.0;


    // Perform PI control
        // Calculate error
        // Negative if velocity too high, positive if too low
    l_error = l_d_vel - l_avg; // TODO: This was always 50 - 0,500,1000 before moving average filter
    r_error = r_d_vel - r_avg;

        // Calculate integrated error
    l_eint += l_error;
    r_eint += r_error;
        // Cap integrated error
    if(l_eint > MAX_E_CAP)
        l_eint = MAX_E_CAP;
    else if(l_eint < MIN_E_CAP)
        l_eint = MIN_E_CAP;
    if(r_eint > MAX_E_CAP)
        r_eint = MAX_E_CAP;
    else if(r_eint < MIN_E_CAP)
        r_eint = MIN_E_CAP;
    
        // Calculate desired PWM
    l_d_pwm = L_KP *l_error + L_KI * l_eint;
    r_d_pwm = R_KP *r_error + R_KI * r_eint;
    //TODO Because of the high read frequency compared to the wheel speed, I expect the numbers here to set the pwm to 50, 
    // then as soon as motion is registered set it back to 0 due to being too fast. 
    // The moving average filter will hopefully address this issue

        // Cap desired value to range
    if(l_d_pwm > MAX_PWM)
        l_d_pwm = MAX_PWM;
    else if(l_d_pwm < MIN_PWM)
        l_d_pwm = MIN_PWM;
    if(r_d_pwm > MAX_PWM)
        r_d_pwm = MAX_PWM;
    else if(r_d_pwm < MIN_PWM)
        r_d_pwm = MIN_PWM;

    // Set duty cycle based on controller output
        // Set OCxRS = Duty% * (PRx +1)/100;
    OC1RS = l_d_pwm * (PR2 + 1) /100;
    OC4RS = r_d_pwm * (PR2 + 1) /100;
//    OC1RS = 2000;
//    OC4RS = 2000;

    // TODO this is debug output data
    _l_global = r_error;
    _r_global = r_eint;


    // Save the new counts
    l_prev_count = l_count;
    r_prev_count = r_count;

    // Clear Flag
    IFS0bits.T4IF = 0;
}

/*******************************************************************************
 End of File
*/
