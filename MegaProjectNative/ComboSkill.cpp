#include "StdAfx.h"
#include "ComboSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

ComboSkill::ComboSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

ComboSkill::~ComboSkill(void)
{

}

void ComboSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void ComboSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void ComboSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void ComboSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void ComboSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode ComboSkill::getOpcode()
{
	return SkillOpcode::Combo;
}