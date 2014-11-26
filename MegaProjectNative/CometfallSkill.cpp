#include "StdAfx.h"
#include "CometfallSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

CometfallSkill::CometfallSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

CometfallSkill::~CometfallSkill(void)
{

}

void CometfallSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void CometfallSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void CometfallSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void CometfallSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void CometfallSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode CometfallSkill::getOpcode()
{
	return SkillOpcode::Cometfall;
}