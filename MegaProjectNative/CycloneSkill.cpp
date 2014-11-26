#include "StdAfx.h"
#include "CycloneSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "Actor.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

CycloneSkill::CycloneSkill(Game::Player* _owner, Game::Actor* _target)
	:ISkill(_owner, 5000)
{
	this->target = _target;
}

CycloneSkill::~CycloneSkill(void)
{

}

void CycloneSkill::start()
{
	ISkill::start();
	this->owner->setBaseAnimationSpeed(0.8);
	this->owner->lookAt(this->target->getPosition());
	this->owner->PlayAnimation("Skill_Class02_Cyclone", false);

	this->owner->canWalk = false;

	if (this->owner->isMoving)
	{
		this->owner->StopMoving();
	}

	this->owner->TranslateTo(this->target->getPosition(), 90);
}

void CycloneSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void CycloneSkill::finish()
{
	ISkill::finish();
	this->owner->restoreBaseAnimationSpeed();
	this->owner->PlayAnimation("Idle", true);
	this->owner->canWalk = true;

	if (this->owner->isTranslating)
		this->owner->StopTranslating();
}

void CycloneSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void CycloneSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Cyclone")
	{
		this->finish();
	}
}

SkillOpcode CycloneSkill::getOpcode()
{
	return SkillOpcode::Cyclone;
}