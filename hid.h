#ifndef HID_H_INCLUDED
#define HID_H_INCLUDED

void SetupFeatureReport(byte reportID);
void SetupOutputReport(byte reportID);

void SetFeatureReport(byte reportID);
void GetFeatureReport(byte reportID);

void SetOutputReport(byte reportID);
void GetInputReport(byte reportID);


#endif
