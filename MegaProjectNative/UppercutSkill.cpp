#include "StdAfx.h"
#include "UppercutSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

UppercutSkill::UppercutSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

UppercutSkill::~UppercutSkill(void)
{

}

void UppercutSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Uppercut", false);

	this->owner->canWalk = false;
}

void UppercutSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void UppercutSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void UppercutSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void UppercutSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Uppercut")
	{
		this->finish();
	}
}

SkillOpcode UppercutSkill::getOpcode()
{
	return SkillOpcode::Uppercut;
}