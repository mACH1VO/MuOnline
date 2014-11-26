#include "StdAfx.h"
#include "FlameSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

FlameSkill::FlameSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

FlameSkill::~FlameSkill(void)
{

}

void FlameSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void FlameSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void FlameSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void FlameSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void FlameSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode FlameSkill::getOpcode()
{
	return SkillOpcode::Flame;
}