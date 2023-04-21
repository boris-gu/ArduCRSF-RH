# ArduCRSF-RH
Arduino library for communicating with external module via CRSF protocol (just like radio handset do)

## Wiring Diagram 
ESP32 -> Inverter -> ELRS TX  
![ELRS_base](/img/ELRS_base.png)

## SoftSerial
When using SoftSerial it is possible that data transmission errors occur.  
Known bug: for some unknown reason channel 5 (if starting from 0) must be less than 512, otherwise the packet will not be received.

The maximum baud rate is limited to 115200