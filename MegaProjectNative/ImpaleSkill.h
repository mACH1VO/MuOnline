#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class ImpaleSkill : public ISkill
{
public:
	ImpaleSkill(Game::Player* _owner);
	~ImpaleSkill(void);


	SkillOpcode ImpaleSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void ImpaleSkill::onAnimationStarted(string name);
	virtual void ImpaleSkill::onAnimationEnded(string name);
};

