#pragma once
#include <Arduino.h>

class BoundRotary
{
	int32_t mValue;
	int32_t mLowValue;
	int32_t mHighValue;

	int32_t * mHighBound;
	int32_t * mLowBound;

	bool mSwitch = false;
public:
	int32_t value()
	{
		return mValue;
	}

	BoundRotary() :
		mValue(0), mLowValue(0), mHighValue(127)
	{
		mode(false);
	}

	void update(uint8_t direction)
	{
		mValue += (direction==2)-(direction==1);
		if( mValue > mHighValue ) mValue = (*mHighBound);
		else if( mValue < mLowValue ) mValue = (*mLowBound);
	}

	void mode(bool cyclic)
	{
		if (cyclic)
		{
			mHighBound = &mLowValue;
			mLowBound = &mHighValue;
		}
		else
		{
			mLowBound = &mLowValue;
			mHighBound = &mHighValue;
		}
	}

	void bounds(int32_t low, int32_t high)
	{
		mLowValue = low;
		mHighValue = high;
	}
};
