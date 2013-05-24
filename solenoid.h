// Acutation of a solenoid on PIC 18F2455 (and siblings)
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
#ifndef SOLENOID_H
#define SOLENOID_H

// Resources:
//    AN0      - Voltage feedback from boost circuit
//    RA5      - Turn on to fire solenoid
//    RC1/CCP2 - PWM input to inductor based boost circuit

void configSolenoid();
void actuateSolenoid();
void clearSolenoid();

unsigned char getSolenoidVoltage(); // Get current value from voltage boost
void checkSolenoidVoltage();        // Ensure voltage is in bounds

#endif // SOLENOID_H
