#pragma once
#include "stdafx.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class ISkill
{
public:
	ISkill(Game::Player* _owner, int _timeOut);
	virtual ~ISkill(void);

	std::string name;
	Game::Player* owner;
	TickTimer* tt_timeOut;
	bool isFinished;

	float secondsElapsed;

	virtual SkillOpcode getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void onAnimationStarted(string name);
	virtual void onAnimationEnded(string name);
};

