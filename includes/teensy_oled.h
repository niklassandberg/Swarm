#pragma once

#include <boundparameters.h>

#include "u8g_i2c.h"

u8g_t gU8g;

uint8_t x = 0;

void u8g_DrawHollowBox(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h)
{
	u8g_DrawHLine(&gU8g, x, y, w);
	u8g_DrawHLine(&gU8g, x, y+h, w+1);
	u8g_DrawVLine(&gU8g, x, y, h);
	u8g_DrawVLine(&gU8g, x+w, y, h);
}

class UIBoxValue
{
	uint8_t mValue;
	uint8_t mX;
	uint8_t mY;
	uint8_t mW;
	uint8_t mH;

	BoundRotary * mRotary;

	char mName[8];
	char mPrefix[8];

public:

	UIBoxValue()
	{

	}

	BoundRotary * rotary(BoundRotary * r)
	{
		mRotary = r;
		return mRotary;
	}

	BoundRotary * rotary()
	{
		return mRotary;
	}

	void updateValue()
	{
		uint8_t value = mRotary->value()>>4;
		mValue = value;
		if(mValue>64) mValue = 64;
	}

	void init( u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h)
	{
		mX = x;
		mY = y;
		mW = w;
		mH = h;
	}

	const char * name(const char * n)
	{
		strncpy ( mName, n, 8 );
		return mName;
	}

	char * prefix(const char * p)
	{
		strncpy ( mPrefix, p, 8 );
		return mPrefix;
	}

	char * prefix()
	{
		return mPrefix;
	}

	const char * name()
	{
		return mName;
	}

	void value(uint8_t value)
	{
		if(value>64) mValue = 64;
		else mValue = value;
	}

	void render(u8g_t *u8g)
	{
		u8g_DrawHollowBox(u8g, mX , mY, mW, mH);
		u8g_DrawBox      (u8g, mX , 1 + mH - mValue, mW, mH);
	}
};

class UITextParameter
{

	BoundRotary * mRotary;

	char mName[8];
	char mPrefix[8];

	BoundRotary * rotary(BoundRotary * r)
	{
		mRotary = r;
		return mRotary;
	}

	BoundRotary * rotary()
	{
		return mRotary;
	}

public:

	UITextParameter()
	{

	}

	char * prefix()
	{
		return mPrefix;
	}

	const char * name()
	{
		return mName;
	}

	void value(uint8_t value)
	{
//		if(value>64) mValue = 64;
//		else mValue = value;
	}


};

#define BOX_WIDTH 10
#define BOX_SPACE 2
#define BOX_HEIGTH 63

UIBoxValue boxes[6];

typedef const char * NAME;
typedef const char * PREFIX;

template<
    class T1,
    class T2
> struct pair
{
	T1 first;
	T2 second;

	pair(const T1& f, const T2& s) : first(f), second(s)
	{}
};


enum DISPLAY_VIEW
{
	Boxes,
	Parameter
};

UIBoxValue * gLastChange = NULL;
void (*view_fn)();


void parameterView()
{
	if(gLastChange==NULL)
	{
		return;
	}

	char buffer[32];

	u8g_FirstPage(&gU8g);
	do {
		u8g_DrawBox(&gU8g, 0 , 0, 26, 14); //selected
		//u8g_DrawHollowBox(&gU8g, 0 , 0, 23, 13); //unselected

		u8g_SetColorIndex(&gU8g, 0);
		u8g_DrawStr(&gU8g, 4, 11, gLastChange->name());
		u8g_SetColorIndex(&gU8g, 1);

		sprintf(
				buffer,
				"%11ld %2s",
				gLastChange->rotary()->value(),
				gLastChange->prefix()
		);

		u8g_DrawHollowBox(&gU8g, 26 , 0, 98, 13); //unselected
		u8g_DrawStr(&gU8g, 36, 11, buffer);


	} while(u8g_NextPage(&gU8g));

}

void globalParameterView()
{
	for(size_t x = 0 ; x < 6 ; ++x)
		boxes[x].updateValue();

	u8g_FirstPage(&gU8g);
	do {
		for(size_t x = 0 ; x < 6 ; ++x)
			boxes[x].render(&gU8g);

	} while(u8g_NextPage(&gU8g));
}

void updateDisplay()
{
	view_fn();
}

void lastChangeParameter(uint8_t index)
{
	gLastChange = &(boxes[index]);
}

void swithChangeInnerParameter(uint8_t index)
{
	gLastChange = &(boxes[index]);
}

void displayView(DISPLAY_VIEW view)
{
	switch (view) {
		case Boxes:
			view_fn = globalParameterView;
			break;
		case Parameter:
			view_fn = parameterView;
			break;
		default:
			break;
	}
}

void initDisplay (BoundRotary * test[])
{
	delay(100);
	// init display:
	u8g_InitComFn(&gU8g, &u8g_dev_sh1106_128x64_i2c, u8g_com_hw_i2c_fn);
	// font , color
	u8g_SetFont(&gU8g, u8g_font_6x13r);
	u8g_SetColorIndex(&gU8g, 1);

	const pair< NAME, PREFIX > metadata[]  =
	{
		pair<NAME,PREFIX>("Pos","ms"),
		pair<NAME,PREFIX>("Dur","ms"),
		pair<NAME,PREFIX>("Trg","ms"),
		pair<NAME,PREFIX>("Pch","X "),
		pair<NAME,PREFIX>("Amp","X "),
		pair<NAME,PREFIX>("Shp","% "),
	};

	for(size_t x = 0 ; x < 6 ; ++x)
	{
		boxes[x].init( x * (BOX_WIDTH + BOX_SPACE),
				0, BOX_WIDTH, BOX_HEIGTH);
//		boxes[x].rotary( &(test[x]) );
		boxes[x].name(metadata[x].first);
		boxes[x].prefix(metadata[x].second);
	}

	view_fn = globalParameterView;
}
