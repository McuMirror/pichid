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
//
#include <pic18fregs.h>
#include "servo.h"

static unsigned char servo1PulseState; // Lets ISR know if pulse starting or ending

static unsigned char servo1Value;   // Desired position of servo
static unsigned int servo1TMRValue; // Timer 3 value to achieve desired position

static unsigned char sCnt;

#if 0
// For servo values from 0..127
#define DEAD_ZONE_LOW 60
#define DEAD_ZONE_HIGH 68
#define DEAD_ZONE_DELTA 7
#define TIMER3_SCALE 25
#else
// For servo values from 0..255
#define DEAD_ZONE_LOW 125
#define DEAD_ZONE_HIGH 131
#define DEAD_ZONE_DELTA 5
#define TIMER3_SCALE 12
#endif

// Given a servo value, compute the starting value for Timer 3
// to get the right pulse length.  A small dead zone is inserted in
// the middle to reduce jitter.  The size of the zone is calculated
// to make the division into desired ticks come out even.
int computeTMRValue(unsigned char servoValue)
{
    unsigned int width;

    width = servo1Value;

	// Add dead zone by squashing the center values together
    if (width > DEAD_ZONE_LOW)
    {
        if (width < DEAD_ZONE_HIGH)
            width = DEAD_ZONE_LOW;
        else
            width -= DEAD_ZONE_DELTA;
    }

	// Stretch the value to cover the number of ticks in 1 msec
	width *= TIMER3_SCALE;

	// The timer rolls over at 0x10000.  The maximum pulse length is
	// 2 msec.  The input to the timer, on a 48 MHz Fosc, and after
	// 1:4 prescale is 3 MHz.  This gives 3000 (0xbb8) ticks per msec.
	// The desired pulse duration is added to that, and that sum
	// subtracted from the rollover point of the timer.
    width = 0xf448 - width; // 0x10000 - (0xbb8 + width)

	return width;
}

void servo1ISR()
{
    PIE2bits.TMR3IE  = 0; // Disable interrupts on Timer 3 until configured
    T3CONbits.TMR3ON = 0; // Turn off Timer 3 until configured

#if 0
	// Non-ISR based routine
    // Set timer high and low bytes
    TMR3H = (servo1TMRValue & 0xff00) >> 8;
    TMR3L = (servo1TMRValue & 0xff);

    // Start the pulse to the servo
    SERVO1_PIN = 1;

    PIR2bits.TMR3IF  = 0; // Ensure overflow flag is clear
    T3CONbits.TMR3ON = 1; // Turn Timer 3 on
    while (!PIR2bits.TMR3IF)
		;
		
    // End the pulse to the servo
    SERVO1_PIN = 0;

    // Wait for another 1/45th of a second before
    // the next pulse
    TMR3H = 0;
    TMR3L = 0;
#else
    if (!servo1PulseState)
    {
        // Set timer high and low bytes
        TMR3H = (servo1TMRValue & 0xff00) >> 8;
        TMR3L = (servo1TMRValue & 0xff);

        // Start the pulse to the servo
        SERVO1_PIN = 1;
    }
    else
    {
        // End the pulse to the servo
        SERVO1_PIN = 0;

        // Wait for another 1/45th of a second before
        // the next pulse
        TMR3H = 0;
        TMR3L = 0;
    }
#endif

    // Toggle the state of the pulse
    servo1PulseState = 1 - servo1PulseState;

    PIR2bits.TMR3IF  = 0; // Ensure overflow flag is clear
    PIE2bits.TMR3IE  = 1; // Enable interrupts for Timer 3
    T3CONbits.TMR3ON = 1; // Turn Timer 3 on
}

void configServos()
{
	sCnt = 0;

    PIE2bits.TMR3IE  = 0; // Disable interrupts on Timer 3 until configured

	T3CON = 0x20; // FOsc/4 input, Timer 3 off, 1:4 prescale (3 MHz input to T3)

    // Set Timer 3 to overflow after 65536 (2^16) ticks, which at 3 MHz
    // corresponds to about 45 times a second.
    TMR3H = 0;
    TMR3L = 0;

    // Ensure the pin associated with Servo 1 is digital output
    SERVO1_MASK = 0;

    // Set pulse off
    servo1PulseState = 0;
    SERVO1_PIN = 0;

    // Set the servo value to the center position
    servo1Value = 0x40;

	// Cache the timer value
	servo1TMRValue = computeTMRValue(servo1Value);

	// Set interrupt/control flags for Timer 3
    PIR2bits.TMR3IF  = 0; // Clear Timer 3 interrupt flag
    IPR2bits.TMR3IP  = 0; // Low priority for Timer 3 interrupt
    PIE2bits.TMR3IE  = 1; // Enable interrupts for Timer 3
    T3CONbits.TMR3ON = 1; // Turn Timer 3 on
}

void setServo1(unsigned char width)
{
    servo1Value    = width;
	servo1TMRValue = computeTMRValue(servo1Value);
}

unsigned char getServo1()
{
    return servo1Value;
}
