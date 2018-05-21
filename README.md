# Swarm
Advanced granular effect pedal for guitarist. Code base is highly depended on Teensyduino. This will maybe be changed in the future.

## Configuration/Setup

### Hardware
* Teensy 3.6
* Teensy audio board
* atmega328p
* 6 rotary encoder
* Oled 128x64, chipset SH1106

### Prodject dependencies

TODO: fill in rotary encoder project.


### IDE setup
1. Install Arduino IDE https://www.arduino.cc/en/Main/Software
2. Install Teensyduino https://www.pjrc.com/teensy/teensyduino.html
3. Install Sloeber http://eclipse.baeyens.it/ (maybe not needed but makes life more simple then Arduino IDE, Arduino IDE still needs to be installed because Teensyduino has it as bependency)
4.1. Launch Sloeber, open menu Arduino->Preference.
4.2. Add the following configuration.
4.2.1. ```Private Libary path: [Path to arduino dir]/Arduino/hardware/teensy/avr/libraries```
4.2.2. ```Private hardware path: [Path to arduino dir]/Arduino/hardware/teensy/avr```
5. Oled 128x64, chipset SH1106 configuration: Wire is not compatible with SH1106 u8g. i2c_t3 is. Possible fix see below.
5.1. Open [Path to arduino dir]/Arduino/hardware/teensy/avr/libraries/Wire.h
5.1. Replace everything with 
```
#ifndef TwoWire_h
#define TwoWire_h

#include <i2c_t3.h>

typedef i2c_t3 TwoWire;

#endif
```
5.2. Delete Wire.cpp and possible WireKinetis files if Arduino IDE is in use.
.....
