/*
  RFSniffer

  Usage: ./RFSniffer [-h] [PIN] [pulselength]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer

*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 29;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }

     int pulseLength = 0;
	 if (argc >= 2) {
		 if ( strcmp(argv[1],"-h")==0 or strcmp(argv[1],"--help")==0 or strcmp(argv[1],"-?")==0 ){
			printf("Usage: %s [-h] [PIN] [pulselength]\n", argv[0]);
			printf("-h\t- this help\n");
			printf("PIN\t- where receiver is connect to RPi, consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/ ,defaut is 29\n");
			printf("pulselength\t- base pulselength in microseconds\n");
			return -1;
		 }
		 else {
			PIN = atoi(argv[1]);
		}
	 }
     if (argc >= 3) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt
     
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
   
          //printf("Received %i %s\nReceived n %s\n", mySwitch.getReceivedProtocol(), mySwitch.getReceiveBinString(), mySwitch.getLastReceiveBinString() );
          printf("Received %s %i\n", mySwitch.getReceiveBinString(), mySwitch.getReceivedProtocol() );
        }
		fflush(stdout); //need for futer process result in pipe
    
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}

