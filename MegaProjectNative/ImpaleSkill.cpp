#include "StdAfx.h"
#include "ImpaleSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

ImpaleSkill::ImpaleSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

ImpaleSkill::~ImpaleSkill(void)
{

}

void ImpaleSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void ImpaleSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void ImpaleSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void ImpaleSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void ImpaleSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode ImpaleSkill::getOpcode()
{
	return SkillOpcode::Impale;
}