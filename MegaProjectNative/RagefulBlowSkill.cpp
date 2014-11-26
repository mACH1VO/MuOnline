#include "StdAfx.h"
#include "RagefulBlowSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

RagefulBlowSkill::RagefulBlowSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

RagefulBlowSkill::~RagefulBlowSkill(void)
{

}

void RagefulBlowSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_DeathStab", false);

	this->owner->canWalk = false;
}

void RagefulBlowSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void RagefulBlowSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void RagefulBlowSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void RagefulBlowSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_DeathStab")
	{
		this->finish();
	}
}

SkillOpcode RagefulBlowSkill::getOpcode()
{
	return SkillOpcode::RagefulBlow;
}