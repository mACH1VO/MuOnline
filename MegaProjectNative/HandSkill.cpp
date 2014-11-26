#include "StdAfx.h"
#include "HandSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "Map.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"

HandSkill::HandSkill(Game::Player* _owner, Game::Actor* _target)
	:ISkill(_owner, 5000)
{
	this->target = _target;
}

HandSkill::~HandSkill(void)
{

}

void HandSkill::start()
{
	ISkill::start();
	this->owner->setBaseAnimationSpeed(0.8);
	this->owner->lookAt(this->target->getPosition());
	this->owner->PlayAnimation("Attack_Class02_Hand", false);
	this->owner->canWalk = false;

	if (this->owner->isMoving)
	{
		this->owner->StopMoving();
	}
}

void HandSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void HandSkill::finish()
{
	ISkill::finish();
	this->owner->restoreBaseAnimationSpeed();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
}

void HandSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void HandSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Attack_Class02_Hand")
	{
		this->finish();
	}
}

SkillOpcode HandSkill::getOpcode()
{
	return SkillOpcode::Hand;
}