# Swarm
Advanced granular effect pedal for guitarist. Code base is highly depended on Teensyduino. This will maybe be changed in the future.

## Configuration/Setup

### Hardware
Teensy 3.6
Teensy audio board
atmega328p
6 rotary encoder
Oled 128x64, chipset SH1106

### IDE setup
1. Install Arduino IDE https://www.arduino.cc/en/Main/Software
2. Install Teensyduino https://www.pjrc.com/teensy/teensyduino.html
3. Install Sloeber http://eclipse.baeyens.it/ (maybe not needed but makes life more simple then Arduino IDE, Arduino IDE still needs to be installed because Teensyduino has it as bependency)
4. Launch Sloeber, open menu Arduino->Preference.
5. Add the following configuration.
6. ```Private Libary path: [Path to arduino dir]/Arduino/hardware/teensy/avr/libraries```
7. ```Private hardware path: [Path to arduino dir]/Arduino/hardware/teensy/avr```
8. For oled with chipset SH1106
