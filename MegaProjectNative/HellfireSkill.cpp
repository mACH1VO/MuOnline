#include "StdAfx.h"
#include "HellfireSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

HellfireSkill::HellfireSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

HellfireSkill::~HellfireSkill(void)
{

}

void HellfireSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void HellfireSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void HellfireSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void HellfireSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void HellfireSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode HellfireSkill::getOpcode()
{
	return SkillOpcode::Hellfire;
}