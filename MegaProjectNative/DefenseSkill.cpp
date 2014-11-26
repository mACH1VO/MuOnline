#include "StdAfx.h"
#include "DefenseSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

DefenseSkill::DefenseSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

DefenseSkill::~DefenseSkill(void)
{

}

void DefenseSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void DefenseSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void DefenseSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void DefenseSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void DefenseSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode DefenseSkill::getOpcode()
{
	return SkillOpcode::Defense_;
}