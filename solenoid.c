// Firmware framework for USB I/O on PIC 18F2455 (and siblings)
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
#include "solenoid.h"

// Actuate solenoid by pulling RA5 high; disable by clearing RA5
#define FIRE_SOLENOID() PORTAbits.RA5 = 1
#define CLEAR_SOLENOID() PORTAbits.RA5 = 0
// Enable RC1/CCP2 by setting pin as an output
#define EnablePWM() TRISCbits.TRISC1 = 0
// Disable P1A/RB3 by setting pin as an input
#define DisablePWM() TRISCbits.TRISC1 = 1

// Set the duty cycle.  With PR2 set at 0x7f (see main.c), the
// value 0x20 will give about a 25% duty cycle.  This should
// be adjusted based on the current capacity of the chosen
// inductor, the desired voltage, and the speed at which
// the voltage is generated.
#define DEFAULT_DUTY_CYCLE 0x20

// Counter for how often the output voltage is checked.
static unsigned char voltCtr;

void configSolenoid()
{
    voltCtr = 0;

    // Using RA5 to send fire signal
    TRISAbits.TRISA5 = 0; // Set RA5 as an output

    // Configure PWM to drive voltage booster
    CCP2CON = 0x0c; // Single PWM output, LSBs set to 0, PWM mode
    CCPR2L = DEFAULT_DUTY_CYCLE;  // Test duty cycle

    EnablePWM();
}

// Read an analog value on AN0
unsigned char getSolenoidVoltage()
{
    // TBD: Wait acquisition time?

    // Start conversion
    ADCON0bits.GO = 1;

    // Wait until conversion complete
    while (ADCON0bits.GO)
        ;

    // Return the top 8 bits of the result
    return ADRESH;
}

void disableSolenoidVoltage()
{
    DisablePWM();
}

void enableSolenoidVoltage()
{
    EnablePWM();
}

// Check voltage - if above threshold then disable PWM.  The circuit
// checks voltage between a 56K and 10K resistor.  This means that
// the actual voltage will be 6.6 * measured voltage.
#define HIGH_SET_POINT 0xD0 // ~0.85 * Vdd
#define LOW_SET_POINT  0xCC // ~0.8 * Vdd
// For the set points above (0xd0/0xcc), together with losses in the
// circuit, the voltage is maintained between about 20V and 21V.
void checkSolenoidVoltage()
{
    unsigned char voltage;

    voltCtr++;
    if (voltCtr != 0)
        return;

    voltage = getSolenoidVoltage();
    if (voltage > HIGH_SET_POINT)
        disableSolenoidVoltage();
    else if (voltage < LOW_SET_POINT)
        enableSolenoidVoltage();
}

// After appropriate button is pushed, raise the port that fires the solenoid.
// To debounce the firing button, it has to be held down for at least two measurement
// (interrupt) periods
void actuateSolenoid()
{
    // Don't generate voltage when solenoid is firing
    CCPR2L = 0;   // Set duty cycle to 0
    DisablePWM();

    // Send signal to fire the solenoid
    FIRE_SOLENOID();
}

// When the appropriate button is released, clear solenoid actuation flags.
void clearSolenoid()
{
    CLEAR_SOLENOID();

    // After solenoid has fired, start generating voltage again
    CCPR2L = DEFAULT_DUTY_CYCLE;
    EnablePWM();
}
