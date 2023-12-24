# Swarm
Granular effect pedal for guitarist. Code base is highly depended on Teensyduino. This will maybe be changed in the future.

## Configuration/Setup

### Hardware
* Teensy 3.6
* Teensy audio board
* atmega328p
* 6 rotary encoder
* Oled 128x64, chipset SH1106

### Prodject dependencies

https://github.com/niklassandberg/multiple-rotary-encoder
https://github.com/niklassandberg/teensy_audio_extend

### IDE (Sloeber based) setup
1. Install Arduino IDE https://www.arduino.cc/en/Main/Software
2. Install Teensyduino https://www.pjrc.com/teensy/teensyduino.html
3. Install Sloeber http://eclipse.baeyens.it/ (maybe not needed but makes life more simple then Arduino IDE, Arduino IDE still needs to be installed because Teensyduino has it as bependency)
4. Launch Sloeber, open menu Window->Preference, go down to 'Arduino'
5. Add the libary and hardware configuration (Under Arduino15 or /Programe Files/Arudino, its wery strange now): 
```
Private Libary path: ..../hardware/teensy/avr/libraries
Private hardware path: .../hardware/teensy/avr
```
6. Move out `[Arduino_Dir]/Arduino/hardware/teensy/avr/examples` from `avr` directory. It can lead to problems if included in buildpath
7. Add Swarm project to your workspace.

### Oled 128x64, chipset SH1106 configuration: Wire is not compatible with SH1106 u8g. i2c_t3 is. Possible fix see below.
1. Open ```[Arduino_Dir]/Arduino/hardware/teensy/avr/libraries/Wire.h```
2. Replace everything with:
```
#ifndef TwoWire_h
#define TwoWire_h

#include <i2c_t3.h>

typedef i2c_t3 TwoWire;

#endif
```
3. Delete Wire.cpp and WireKinetis files.

### Project configuration.

1. Open project preferences.
2. Go to ```C/C++ General->Path and Symbols.```
4. In includes add FOR ALL: ```[Swarm_Project]/includes```
5. Go to Source Location and add: ```[Swarm_Project]/source```

### Teensy audio extend configuration.

1. Add https://github.com/niklassandberg/teensy_audio_extend to your workspace
2. Open project preferences.
3. Go to ```C/C++ General->Path and Symbols```.
4. In ```includes GNU C++``` add: ```[teensy_audio_extend_Dir]/libraries```
5. Go to ```Source Location``` and add: ```teensy_audio_extend```.
6. Follow instructions on https://github.com/niklassandberg/multiple-rotary-encoder


