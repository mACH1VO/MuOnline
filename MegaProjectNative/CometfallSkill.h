#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class CometfallSkill : public ISkill
{
public:
	CometfallSkill(Game::Player* _owner);
	~CometfallSkill(void);


	SkillOpcode CometfallSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void CometfallSkill::onAnimationStarted(string name);
	virtual void CometfallSkill::onAnimationEnded(string name);
};

