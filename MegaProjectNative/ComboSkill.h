#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class ComboSkill : public ISkill
{
public:
	ComboSkill(Game::Player* _owner);
	~ComboSkill(void);


	SkillOpcode ComboSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void ComboSkill::onAnimationStarted(string name);
	virtual void ComboSkill::onAnimationEnded(string name);
};

