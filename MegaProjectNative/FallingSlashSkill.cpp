#include "StdAfx.h"
#include "FallingSlashSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

FallingSlashSkill::FallingSlashSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

FallingSlashSkill::~FallingSlashSkill(void)
{

}

void FallingSlashSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void FallingSlashSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void FallingSlashSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void FallingSlashSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void FallingSlashSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode FallingSlashSkill::getOpcode()
{
	return SkillOpcode::FallingSlash;
}