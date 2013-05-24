// Control of an R/C type servo on PIC 18F2455 (and siblings)
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
#ifndef SERVO_H
#define SERVO_H

// A pulse width of 1.5 milliseconds positions the servo at its center,
// with 1 millisecond and 2 milliseconds being the accepted limits to either side.

// Resources:
//    Timer 3 - Fire 45 times a second to initiate a pulse to servo
//    RA3     - Pluse output to servo
#define SERVO1_PIN PORTAbits.RA3
#define SERVO1_MASK TRISAbits.TRISA3

void configServos();
void servo1ISR();
void setServo1(unsigned char width);
unsigned char getServo1();

#endif // SERVO_H
