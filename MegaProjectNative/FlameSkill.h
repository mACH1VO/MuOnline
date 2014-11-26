#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class FlameSkill : public ISkill
{
public:
	FlameSkill(Game::Player* _owner);
	~FlameSkill(void);


	SkillOpcode FlameSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void FlameSkill::onAnimationStarted(string name);
	virtual void FlameSkill::onAnimationEnded(string name);
};

