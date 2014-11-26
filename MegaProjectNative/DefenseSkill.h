#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class DefenseSkill : public ISkill
{
public:
	DefenseSkill(Game::Player* _owner);
	~DefenseSkill(void);


	SkillOpcode DefenseSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void DefenseSkill::onAnimationStarted(string name);
	virtual void DefenseSkill::onAnimationEnded(string name);
};

