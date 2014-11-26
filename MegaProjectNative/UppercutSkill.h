#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class UppercutSkill : public ISkill
{
public:
	UppercutSkill(Game::Player* _owner);
	~UppercutSkill(void);


	SkillOpcode UppercutSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void UppercutSkill::onAnimationStarted(string name);
	virtual void UppercutSkill::onAnimationEnded(string name);
};

