#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class SlashSkill : public ISkill
{
public:
	SlashSkill(Game::Player* _owner);
	~SlashSkill(void);


	SkillOpcode SlashSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void SlashSkill::onAnimationStarted(string name);
	virtual void SlashSkill::onAnimationEnded(string name);
};

