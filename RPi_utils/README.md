# About

rcswitch-pi is for controlling rc remote controlled power sockets 
with the raspberry pi. Kudos to the projects [rc-switch](http://code.google.com/p/rc-switch)
and [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi).
I just adapted the rc-switch code to use the wiringpi library instead of
the library provided by the arduino.


## Install

First you have to install the [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) library.
After that you can compile the example program *send* by executing *make*. 
It uses wiringPi pin no 2 by default. You may want to change the used GPIO pin before compilation of the codesend.cpp source file. (Good Resource for Pin Details https://pinout.xyz/pinout/wiringpi)

## Usage
next command must be run as superuser becouse this need used wiringpi.

### for scaning:
```
./RFSniffer [-h] [PIN] [pulselength]
	-h			-	this help
	PIN			-	where receiver is connect to RPi, consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/ ,defaut is 29
	pulselength	-	base pulselength in microseconds
```

*example:*
```
sudo ./RFSniffer
Received 100011111111111110010001 1
Received 100011111111111110010001 1
Received 100011111111111110010001 1
Received 0110011010101001101010010101010101011001010101101001011001010101 7
```

**means of output:**
frist is number binary code and secound is protocol number

###for send:
```
./codesend binarycode [protocol] [PIN] [pulselength]
	binarycode	-	As decoded by RFSniffer\n");
	protocol	-	According to rc-switch definitions or get from command sudo ./RFSniffer
	PIN			-	where transmitter is connect to RPi consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/ ,defaut is 28
	pulselength	-	base pulselength in microseconds
```

use some data format as sudo ./RFSniffer (frist binary code, secount protocol number)

*example:*
```
sudo ./codesend 000010001100001001010000 1
sending code[000010001100001001010000]
```

### howto control remote socket

First, scan control button for your socket. You get binary code and protocol number.
Then use command "codesed" witch previously geting binary code and protocol number.
Generally one code is for on socket and another code is for off socket.

### old command for send
```
./send <systemCode> <unitCode> <command>
```

Command is 0 for OFF and 1 for ON

can be used with old types socket (systemCode and unitCode is decimal code who is set with DIP switch on socket)

## Note
Great use with home automation system etc. domotic more on www.domoticz.com or www.seahu.cz .


