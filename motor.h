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
//
//
// Definitions for motor control
//

//
// Pins used: RC2/CCP1 (Motor PWM), RA1 (MTR1), RA2 (MTR2).  P1A carries the PWM signal
// and is used to drive the enable pin on an SN754410 H-Bridge chip.  MTR1 is high for
// forward and low for reverse; MTR2 is high for reverse and low for forward.  A small
// amount of dead time is inserted when switching between forward and reverse (both
// MTR1 and MTR2 low).
// 
#ifndef MOTOR_H
#define MOTOR_H


void motorInit();
void motorSetSpeed(char speed);
char motorGetSpeed();
void motorOn();
void motorOff();

#endif // MOTOR_H
