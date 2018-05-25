#include "Arduino.h"

#include <main.h>

void printBinary(byte inByte)
{
  for (int b = 7; b >= 0; b--)
  {
  	  Serial.print(bitRead(inByte, b));
  }
  Serial.println();
}

// The loop function is called in an endless loop
int32_t count = 0;

int32_t valTest = 0;

BoundRotary parameters[6][2];
BoundRotary switcher[6];

void initParameters()
{
	for(size_t x = 0 ; x < 6 ; ++x)
	{
//		parameters[x].bounds(0, 1024);
		switcher[x].bounds(0, 1);
	}
}

void setup()
{
	Serial.begin(9600);
	Serial1.begin(19200);

	initAudio();
//	initDisplay(parameters);
	initParameters();

	lastChangeParameter(0);
	displayView(Boxes);
}

uint32_t lastTime = 0;
bool gParameterView = false;

void loop()
{
	uint8_t lastchange = 255;
	while(Serial1.available())
	{
		int16_t protocol = Serial1.read();

		lastchange = protocol>>4;

//		BoundRotary& r = parameters[ lastchange ];
		BoundRotary& sw = switcher[ lastchange ];

//		r.update(protocol & 3);
		sw.update( (protocol>>2) & 3);

		lastChangeParameter(lastchange);
		swithChangeInnerParameter(sw.value());
	}

	if(lastchange != 255)
	{
		lastChangeParameter(lastchange);
		displayView(Parameter);
		lastTime = millis();
		gParameterView = true;
	}
	else if(gParameterView)
	{
		uint32_t now = millis();
		if(now-lastTime>1000)
		{
			displayView(Boxes);
			gParameterView = false;
		}
	}

	updateDisplay();
	loopAudio();
}
