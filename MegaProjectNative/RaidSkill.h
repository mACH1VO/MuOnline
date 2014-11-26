#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class RaidSkill : public ISkill
{
public:
	RaidSkill(Game::Player* _owner);
	~RaidSkill(void);


	SkillOpcode RaidSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void RaidSkill::onAnimationStarted(string name);
	virtual void RaidSkill::onAnimationEnded(string name);
};

