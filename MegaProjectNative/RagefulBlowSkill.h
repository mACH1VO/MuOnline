#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class RagefulBlowSkill : public ISkill
{
public:
	RagefulBlowSkill(Game::Player* _owner);
	~RagefulBlowSkill(void);


	SkillOpcode RagefulBlowSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void RagefulBlowSkill::onAnimationStarted(string name);
	virtual void RagefulBlowSkill::onAnimationEnded(string name);
};

