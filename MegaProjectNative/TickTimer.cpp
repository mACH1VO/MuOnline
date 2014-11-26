#include "StdAfx.h"
#include "TickTimer.h"


TickTimer::TickTimer(int timeOutLong)
{
	this->startTick = GetTickCount();
	this->timeOutLong = timeOutLong;
	this->lastCallTick = startTick;
}


TickTimer::~TickTimer(void)
{
	
}

bool TickTimer::TimedOut()
{
   return GetTickCount() >= (this->startTick + timeOutLong); 
}

int TickTimer::RemainMS()
{
		if ((startTick + timeOutLong) - GetTickCount() > 0)
		{
			return (startTick + timeOutLong) - GetTickCount();
		}
		else
		{
			return -1;
		}
}

unsigned long TickTimer::Elapsed()
{
	return (GetTickCount() - this->startTick); 
}

void TickTimer::Reset()
{
	this->startTick = GetTickCount();
	this->lastCallTick = this->startTick;
	this->resetTimes++;
}

void TickTimer::Reset(int newLong)
{
	this->timeOutLong = newLong;
	this->startTick = GetTickCount();
	this->lastCallTick = this->startTick;
	this->resetTimes++;
}