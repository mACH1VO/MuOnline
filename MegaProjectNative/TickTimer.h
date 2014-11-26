#pragma once
#include "stdafx.h"

class TickTimer
{
public:
	TickTimer(int timeOutLong);
	~TickTimer(void);

	int resetTimes;
	unsigned long startTick;
	int timeOutLong;
	unsigned long lastCallTick;

	bool TimedOut();
	int RemainMS();
	unsigned long Elapsed();
	void Reset();
	void Reset(int newLong);

};

