#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class StrikeofDestructionSkill : public ISkill
{
public:
	StrikeofDestructionSkill(Game::Player* _owner);
	~StrikeofDestructionSkill(void);


	SkillOpcode StrikeofDestructionSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void StrikeofDestructionSkill::onAnimationStarted(string name);
	virtual void StrikeofDestructionSkill::onAnimationEnded(string name);
};

