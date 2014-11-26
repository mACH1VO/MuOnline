#pragma once
#include "stdafx.h"

class GameGlobals
{
public:
	GameGlobals(void);
	~GameGlobals(void);

	static bool FPS_LIMITER;
	static int FPS_LIMIT;

	static bool PACKET_TIMER_LIMITER;
	static int PACKET_TIMER_MS;
};



