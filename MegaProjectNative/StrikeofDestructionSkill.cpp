#include "StdAfx.h"
#include "StrikeofDestructionSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

StrikeofDestructionSkill::StrikeofDestructionSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{

}

StrikeofDestructionSkill::~StrikeofDestructionSkill(void)
{

}

void StrikeofDestructionSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
}

void StrikeofDestructionSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void StrikeofDestructionSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void StrikeofDestructionSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void StrikeofDestructionSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode StrikeofDestructionSkill::getOpcode()
{
	return SkillOpcode::Strike_of_Destruction;
}