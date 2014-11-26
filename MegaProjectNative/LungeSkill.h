#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class LungeSkill : public ISkill
{
public:
	LungeSkill(Game::Player* _owner);
	~LungeSkill(void);


	SkillOpcode LungeSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void LungeSkill::onAnimationStarted(string name);
	virtual void LungeSkill::onAnimationEnded(string name);
};

