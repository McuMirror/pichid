#include <pic18fregs.h>
#include "usb.h"
#include <string.h>


// HID feature buffer
volatile unsigned char HIDFeatureBuffer[HID_FEATURE_REPORT_BYTES];


// Initialization for a SET_FEATURE request.  This routine will be
// invoked during the setup stage and is used to set up the buffer
// for receiving data from the host
void SetupFeatureReport(byte reportID)
{
    if (reportID == 0)
    {
        // When the report arrives in the data stage, the data will be
        // stored in HIDFeatureBuffer.
        inPtr = (byte*)&HIDFeatureBuffer;
    }
}

// Post processing for a SET_FEATURE request.  After all the data has
// been delivered from host to device, this will be invoked to perform
// application specific processing.
void SetFeatureReport(byte reportID)
{
#if DEBUG_PRINT
    //printf("SetFeatureReport(0x%hx)\r\n", reportID);
#endif
    // Currently only handling report 0, ignore any others.
    if (reportID == 0)
    {
        byte solenoidFlag = HIDFeatureBuffer[3];

        // Set the state of the LED based on bit 0 of the first byte
        // of the feature report.
        PORTAbits.RA4 = (HIDFeatureBuffer[0] & 0x01);
        LATD = HIDFeatureBuffer[0];

        // Set the speed of the motor based on the second byte
        //motorSetSpeed((char)(HIDFeatureBuffer[1] - 128));

        // Set the servo position based on the third byte
        //setServo1(HIDFeatureBuffer[2]);

        // Fire the solenoid if bit 0 of the fourth byte is set
        // solenoidFlag = HIDFeatureBuffer[3]; // Workaround - bad code if HIDFeatureBuffer[3] & 0x01 in if statement
        //if (solenoidFlag & 0x01)
        //{
            // Fire the solenoid
            //actuateSolenoid();
        //}
        //else
        //{
            // Turn off power to the solenoid
            //clearSolenoid();
        //}
    }
}

// Handle a feature report request on the control pipe
void GetFeatureReport(byte reportID)
{
#if DEBUG_PRINT
    //printf("GetFeatureReport(0x%uhx): 0x%hx, 0x%hx\r\n",
    //    (byte)reportID, (byte)HIDFeatureBuffer[0],
    //    (byte)HIDFeatureBuffer[1]);
#endif
    if (reportID == 0)
    {
        // Handle report #0
        outPtr = (byte *)&HIDFeatureBuffer;
        HIDFeatureBuffer[0] = PORTA;
        HIDFeatureBuffer[1] = PORTB;
        HIDFeatureBuffer[2] = PORTC;
        //HIDFeatureBuffer[3] = getSolenoidVoltage();
        //HIDFeatureBuffer[4] = motorGetSpeed();
        //HIDFeatureBuffer[5] = getServo1();
		HIDFeatureBuffer[6] = 0;
		if (selfPowered) HIDFeatureBuffer[6] |= 0x01;
		if (remoteWakeup) HIDFeatureBuffer[6] |= 0x02;

        wCount = HID_FEATURE_REPORT_BYTES;
        memcpy(HIDFeatureBuffer, "Bonjour tout le monde           ", wCount);

    }
}

// Handle control out.  This might be an alternate way of processing
// an output report, so all that's needed is to point the output
// pointer to the output buffer
// Initialization for a SET_REPORT request.  This routine will be
// invoked during the setup stage and is used to set up the buffer
// for receiving data from the host
void SetupOutputReport(byte reportID)
{
    if (reportID == 0)
    {
        // When the report arrives in the data stage, the data will be
        // stored in HIDFeatureBuffer
        inPtr = (byte*)&HIDRxBuffer;
    }
}

// Post processing for a SET_REPORT request.  After all the data has
// been delivered from host to device, this will be invoked to perform
// application specific processing.
void SetOutputReport(byte reportID)
{
#if DEBUG_PRINT
    //printf("SetOutputReport(0x%hx)\r\n", reportID);
#endif
    // Currently only handling report 0, ignore any others.
    if (reportID != 0)
        return;

    // TBD: do something.  Not currently implemented because the output
    // report is being handled by an interrupt endpoint.
}

// Handle a control input report
void GetInputReport(byte reportID)
{
#if DEBUG_PRINT
    printf("GetInputReport: 0x%uhx\r\n", reportID);
#endif
    if (reportID == 0)
    {
        // Send back the contents of the HID report
        // TBD: provide useful information...
        outPtr = (byte *)&HIDTxBuffer;

        // The number of bytes in the report (from usb.h).
        wCount = HID_INPUT_REPORT_BYTES;
    }
}
