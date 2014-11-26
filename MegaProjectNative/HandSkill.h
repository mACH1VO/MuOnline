#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
	class Actor;
}
class TickTimer;

enum SkillOpcode;

class HandSkill : public ISkill
{
public:
	HandSkill(Game::Player* _owner, Game::Actor* _target);
	~HandSkill(void);

	Game::Actor* target;
	SkillOpcode HandSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void HandSkill::onAnimationStarted(string name);
	virtual void HandSkill::onAnimationEnded(string name);
};

