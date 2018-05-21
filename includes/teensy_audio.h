#pragma once
#include <Arduino.h>

#include <Audio.h>
#include <effect_grainer.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define SYNCH_MODE_LED 25
#define PICH_NORMAL_LED 27
#define FREEZE_LED 28

AudioEffectGrainer grainer;

AudioInputI2S           i2sIn;
AudioOutputI2S           i2sOut;
AudioControlSGTL5000     sgtl5000;

AudioMixer4              delayCombine;         //xy=301.111328125,232.66671752929688
AudioMixer4              mixerDelayL;         //xy=301.111328125,232.66671752929688
AudioMixer4              mixerDelayR; //xy=302.7778778076172,307.6667594909668
AudioFilterStateVariable filter1;        //xy=522.3335380554199,160.6667881011963
AudioFilterStateVariable filter2; //xy=532.5556678771973,471.55562591552734

//TODO: could be removed if we do production
AudioMixer4              mixerOutL;
AudioMixer4              mixerOutR;


AudioConnection          patchCord1(i2sIn, 0, mixerDelayL, 0);
AudioConnection          patchCord2(i2sIn, 1, mixerDelayR, 0);
AudioConnection          patchCordaa(mixerDelayL, 0, delayCombine, 0);
AudioConnection          patchCordaaa(mixerDelayR, 0, delayCombine, 1);
AudioConnection          patchCord4(delayCombine, 0, grainer, 0);

//-----------

AudioConnection          patchCord658(i2sIn, 0, mixerOutL, 0);
AudioConnection          patchCord649(i2sIn, 1, mixerOutR, 0);
AudioConnection          patchCord638(grainer, 0, mixerOutL, 1);
AudioConnection          patchCord629(grainer, 1, mixerOutR, 1);
AudioConnection          patchCordg618(mixerOutL, 0, i2sOut, 0);
AudioConnection          patchCordg759(mixerOutR, 0, i2sOut, 1);

//AudioConnection          patchCord104(grainer, 0, i2sOut, 0);
//AudioConnection          patchCord105(grainer, 1, i2sOut, 1);

//-----------
AudioConnection          patchCord3(grainer, 0, filter1, 0);
AudioConnection          patchCord5(grainer, 1, filter2, 0);

AudioConnection          patchCord10(filter1, 1, mixerDelayL, 1);
AudioConnection          patchCord12(filter2, 1, mixerDelayR, 1);

void initAudio()
{	//	Serial.begin(9600);

	AudioMemory(880);
	//ps.queueLength(300);

	//out
	sgtl5000.enable();
	sgtl5000.volume(0.5);     // set the main volume...
	sgtl5000.dacVolumeRamp(); //best one.
	sgtl5000.dacVolume(1.0); // (no digital attenuation) at 1.0.

	//in
	sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000.lineInLevel(0, 0);
	sgtl5000.adcHighPassFilterDisable(); // reduce noise.
	grainer.disable(2);
	grainer.disable(3);

	pinMode(FREEZE_LED, OUTPUT);
	pinMode(PICH_NORMAL_LED, OUTPUT);
	pinMode(SYNCH_MODE_LED, OUTPUT);

	delayCombine.gain(0, 0.5f);
	delayCombine.gain(1, 0.5f);
	delayCombine.gain(2, 0.0f);
	delayCombine.gain(3, 0.0f);
}
