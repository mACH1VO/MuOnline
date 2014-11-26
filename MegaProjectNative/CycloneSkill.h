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

class CycloneSkill : public ISkill
{
public:
	CycloneSkill(Game::Player* _owner, Game::Actor* _target);
	~CycloneSkill(void);

	Game::Actor* target;
	SkillOpcode CycloneSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void CycloneSkill::onAnimationStarted(string name);
	virtual void CycloneSkill::onAnimationEnded(string name);
};

