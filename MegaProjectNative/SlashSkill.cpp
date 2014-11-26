#include "StdAfx.h"
#include "SlashSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

SlashSkill::SlashSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

SlashSkill::~SlashSkill(void)
{

}

void SlashSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Slash", false);

	this->owner->canWalk = false;
}

void SlashSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void SlashSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void SlashSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void SlashSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Slash")
	{
		this->finish();
	}
}

SkillOpcode SlashSkill::getOpcode()
{
	return SkillOpcode::Slash;
}