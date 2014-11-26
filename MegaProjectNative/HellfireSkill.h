#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class HellfireSkill : public ISkill
{
public:
	HellfireSkill(Game::Player* _owner);
	~HellfireSkill(void);


	SkillOpcode HellfireSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void HellfireSkill::onAnimationStarted(string name);
	virtual void HellfireSkill::onAnimationEnded(string name);
};

