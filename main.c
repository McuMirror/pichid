// Demonstration code of USB I/O on PIC 18F2455 (and siblings) -
// turn LED on/off and echo a buffer back to host.
//
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
#include <delay.h>
#include "usb.h"
#include "config.h"
#include "hid.h"
#include <string.h>


// HID feature buffer
//volatile unsigned char HIDFeatureBuffer[HID_FEATURE_REPORT_BYTES];

void high_isr(void) __shadowregs __interrupt 1
{
    ;
}

void low_isr(void) __shadowregs __interrupt 2
{
    // If the timer associated with the servo timed out, then
    // ask the servo code to handle it.
    if (PIR2bits.TMR3IF)
    {
        //servo1ISR();
    }
}

// Allocate buffers in RAM for storage of bytes that have either just
// come in from the SIE or are waiting to go out to the SIE.
char txBuffer[HID_INPUT_REPORT_BYTES];
char rxBuffer[HID_OUTPUT_REPORT_BYTES];

// Entry point for user initialization
void UserInit(void)
{
    TRISD = 0;
    LATD = 0xAA;
    delay1mtcy(5);
    LATD = 0x00;

	// Enable interrupts.
	//RCONbits.IPEN   = 1; // Enable priority levels on interrupts
	//INTCONbits.GIEL = 1; // Enable low-priority interrupts
	//INTCONbits.GIEH = 1; // Enable high-priority interrupts
}

// Central processing loop.  Whenever the firmware isn't busy servicing
// the USB, we will get control here to do other processing.
void ApplicationTasks(void)
{
    // User Application USB tasks
    if ((deviceState < CONFIGURED) || (UCONbits.SUSPND==1))
        return;

	// Note: Put tasks here that only make sense if we are attached
	// to the host.

	// Enable interrupts.
	RCONbits.IPEN   = 1; // Enable priority levels on interrupts
	INTCONbits.GIEL = 1; // Enable low-priority interrupts
	INTCONbits.GIEH = 1; // Enable high-priority interrupts
}


// Entry point of the firmware
void main(void)
{
    // Set all I/O pins to digital
    ADCON1 |= 0x0F;

    // Initialize USB
    UCFG = 0x14; // Enable pullup resistors; full speed mode

    deviceState = DETACHED;
    remoteWakeup = 0x00;
    selfPowered = 0x00;
    currentConfiguration = 0x00;

    // Call user initialization function
    UserInit();

    while(1)
    {
        // Ensure USB module is available
        EnableUSBModule();

        // As long as we aren't in test mode (UTEYE), process
        // USB transactions.
        if(UCFGbits.UTEYE != 1)
            ProcessUSBTransactions();

        // Application specific tasks
        ApplicationTasks();
    }
}
