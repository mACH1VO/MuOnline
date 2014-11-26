#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class FallingSlashSkill : public ISkill
{
public:
	FallingSlashSkill(Game::Player* _owner);
	~FallingSlashSkill(void);


	SkillOpcode FallingSlashSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void FallingSlashSkill::onAnimationStarted(string name);
	virtual void FallingSlashSkill::onAnimationEnded(string name);
};

