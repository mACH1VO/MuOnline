#include "StdAfx.h"
#include "LungeSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

LungeSkill::LungeSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

LungeSkill::~LungeSkill(void)
{

}

void LungeSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void LungeSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void LungeSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void LungeSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void LungeSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode LungeSkill::getOpcode()
{
	return SkillOpcode::Lunge;
}