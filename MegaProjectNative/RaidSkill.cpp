#include "StdAfx.h"
#include "RaidSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

RaidSkill::RaidSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

RaidSkill::~RaidSkill(void)
{

}

void RaidSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void RaidSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void RaidSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void RaidSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void RaidSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode RaidSkill::getOpcode()
{
	return SkillOpcode::Raid;
}