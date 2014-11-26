#include "StdAfx.h"
#include "DeathStabSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "Actor.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"
/*
DeathStabSkill::DeathStabSkill(Game::Player* _owner, Game::Actor* _target)
	:ISkill(_owner, 5000)
{
	this->target = _target;

	this->_PSsceneNode = 0;
	this->_particleSystem = 0;
}

DeathStabSkill::~DeathStabSkill(void)
{
	if (this->_PSsceneNode != 0)
	{
		this->_particleSystem->stop();
		this->_PSsceneNode->detachObject(this->_particleSystem);
		std::string psName = this->_particleSystem->getName();

		ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyParticleSystem(this->_particleSystem, GameFramework::getSingletonPtr()->sceneManager);
		GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->_PSsceneNode);
	}
}

void DeathStabSkill::start()
{
	ISkill::start();
	this->owner->setBaseAnimationSpeed(0.7);
	this->owner->lookAt(this->target->getPosition());
	this->owner->PlayAnimation("Skill_Class02_Lunge", false);

	this->owner->canWalk = false;
	if (this->owner->isMoving)
	{
		this->owner->StopMoving();
	}
}

void DeathStabSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void DeathStabSkill::finish()
{
	ISkill::finish();
	this->owner->restoreBaseAnimationSpeed();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;

	if (this->_particleSystem != 0)
		this->_particleSystem->stop();
}

void DeathStabSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void DeathStabSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Lunge")
	{
		this->finish();
	}
}

SkillOpcode DeathStabSkill::getOpcode()
{
	return SkillOpcode::DeathStab;
}*/