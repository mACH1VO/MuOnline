#include "StdAfx.h"
#include "GameGlobals.h"

bool GameGlobals::FPS_LIMITER = false;
int GameGlobals::FPS_LIMIT = 10; //10 = 100fps
bool GameGlobals::PACKET_TIMER_LIMITER = true;
int GameGlobals::PACKET_TIMER_MS = 16;

GameGlobals::GameGlobals(void)
{
}


GameGlobals::~GameGlobals(void)
{
}
