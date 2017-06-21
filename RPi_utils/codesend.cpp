/*
Usage: ./codesend decimalcode [protocol] [pulselength]
decimalcode - As decoded by RFSniffer
protocol    - According to rc-switch definitions
pulselength - pulselength in microseconds

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.

  - former decimalcode was replace binarycode because decimalcode has overlow problem for long data

(Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter 
or your remote control)
*/
#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     

int main(int argc, char *argv[]) {
    
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 28;
    
    // Parse the first parameter to this command as an integer
    int protocol = 0; // A value of 0 will use rc-switch's default value
    int pulseLength = 0;
    int Bitlength = 0;

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s binarycode [protocol] [PIN] [pulselength]\n", argv[0]);
        printf("binarycode\t- As decoded by RFSniffer\n");
        printf("protocol\t- According to rc-switch definitions\n");
        printf("PIN\t- where transmitter is connect to RPi consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/ ,defaut is 28\n");
        printf("pulselength\t- base pulselength in microseconds\n");
        return -1;
    }

    // Change binary code nad protocol accroding to parameters
    //int code = atoi(argv[1]);
    if (argc >= 3) protocol = atoi(argv[2]);
    if (argc >= 4) PIN = atoi(argv[3]);
    if (argc >= 5) pulseLength = atoi(argv[3]);
    
    
    if (wiringPiSetup () == -1) return 1;
    //printf("sending code[%i]\n", code);
    printf("sending code[%s]\n", argv[1]);
    RCSwitch mySwitch = RCSwitch();
    if (protocol != 0) mySwitch.setProtocol(protocol);
    if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
    mySwitch.enableTransmit(PIN);
    
    //mySwitch.send(code, 31);
    mySwitch.send(argv[1]);
    
    return 0;

}
