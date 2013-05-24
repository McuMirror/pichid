// Control of brushed DC motor on PIC 18F2455 (and siblings)
// Copyright (C) 2005 Alexander Enzmann
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include <pic18fregs.h>
#include "motor.h"

// If we try to shift speeds more quickly than the motor can respond, then we can
// cause a latch-up in the controller.  To prevent this, we look at the difference
// between the current speed and the commanded speed  and do not allow changes
// more than MAX_DELTA_SPEED.  This delta is very dependent on the number of times
// per second we try to set the speed (currently assumed to be about 30).  If changes
// are expected more frequently, then this number needs to be smaller (and vice versa).
#define MAX_DELTA_SPEED 4

static volatile char motorSpeed = 0;

// Port dependent declarations for PWM and direction.

// Enable RC2/CCP1 by setting pin as an output - this allows PWM signal to go to the motor.
#define EnablePWM() TRISCbits.TRISC2 = 0
// Disable P1A/RB3 by setting pin as an input
#define DisablePWM() TRISCbits.TRISC2 = 1
// Configure motor direction pins as output
#define ConfigMotorPins() TRISAbits.TRISA1 = 0; TRISAbits.TRISA2 = 0
// Pull direction pins low for both forward and reverse.  Note: never pull them both high,
// that could lead to short circuit and smoke.
#define motorDirectionAllOff() PORTAbits.RA1 = 0; PORTAbits.RA2 = 0
#define motorForwardOn() PORTAbits.RA1 = 1
#define motorReverseOn() PORTAbits.RA2 = 1

void motorInit()
{
    // Start motor speed at 0
    motorSpeed = 0;

    // Set CCP1 as input to prevent bad signals from going to motor.  On the 18f1220
    // this is RB3.
    DisablePWM();

    // Set motor direction pins as outputs (they control motor direction)
    ConfigMotorPins();

    // Set Capture/Compare/PWM register.  Single PWM output, least significant bits
    // set to 0, PWM mode.
    CCP1CON = 0x0c;

    // Set duty cycle
    CCPR1L = 0;

    // Test
    motorSpeed = 0;
    motorOn();
}

char motorGetSpeed()
{
    return motorSpeed;
}

void motorSetSpeed(char speed)
{
    unsigned char i;

#if 0
    // Don't make too big a change in speed all at once.
    char deltaSpeed = motorSpeed - speed;

    if (deltaSpeed < -MAX_DELTA_SPEED)
    {
        motorSpeed -= MAX_DELTA_SPEED;
    }
    else if (deltaSpeed > MAX_DELTA_SPEED)
    {
        motorSpeed += MAX_DELTA_SPEED;
    }
    else
    {
        motorSpeed = speed;
    }
#else
	motorSpeed = speed;
#endif

    // Disable both direction pins (deadtime)
    motorDirectionAllOff();

    // Delay for a couple of microseconds.
    for (i=0;i<24;i++)
        ;

    // Set direction pin based on sign flag of speed.
    if (speed < 0)
    {
        // Pull negative range from -128..-1 to -127..0
        speed = speed + 1;
        speed = -speed;
        motorReverseOn();
    }
    else
    {
        // Positive speed value kept as is.
        motorForwardOn();
    }
    // Shift the 7 bits left so that the top bit is at the top of
    // CCPR1.  TBD: ensure CCP1CON<5:4> are zero
    // CCPR1L = ((speed & 0x7f) << 1);
    CCPR1L = speed;
}

void motorOn()
{
    // Pull RB2 and RB5 low to ensure we don't have both sides active.
    motorDirectionAllOff();
    // Turn on motor by activating enable pin (RB2 high for forward, RB5 high for reverse)
    if (motorSpeed < 0)
        motorReverseOn();
    else
        motorForwardOn();
    // Enable P1A/RB3 by setting pin as an output - this allows PWM signal to go to the motor.
    EnablePWM();
}

void motorOff()
{
    // Disable both forward and reverse
    motorDirectionAllOff();
    // Disable P1A/RB3 by setting pin as an input
    DisablePWM();
}

