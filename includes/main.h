#pragma once

#include <boundparameters.h>
#include <teensy_audio_test.h>
#include <teensy_oled.h>

const int MIN_UPDATE_MS = 10;
uint32_t gReadIntevall = MIN_UPDATE_MS;
uint32_t gPrevMS = 0;

//const float MIN_DURRATION_MS = block2ms(2);
//const float MIN_TRIGG = grainer.bufferMS()*2.0;
//float MAX_POSITION_MS = grainer.bufferMS();


