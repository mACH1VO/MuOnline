#include "StdAfx.h"
#include "InnerSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"
/*
InnerSkill::InnerSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{
	this->_particleSystem = 0;
	this->_PSsceneNode = 0;
}

InnerSkill::~InnerSkill(void)
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

void InnerSkill::start()
{
	ISkill::start();
	this->owner->PlayAnimation("Skill_Class02_Inner", false);

	this->owner->canWalk = false;

	

	this->_PSsceneNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
	this->_PSsceneNode->setPosition(this->owner->getPosition() + Ogre::Vector3::UNIT_Y);

	ParticleUniverse::ParticleSystemManager* pManager =	ParticleUniverse::ParticleSystemManager::getSingletonPtr();
	std::string ps_name = "inner_ps_" + Ogre::StringConverter::toString(this->owner->dynamicId);
	this->_particleSystem = pManager->createParticleSystem(ps_name, "inner", GameFramework::getSingletonPtr()->sceneManager);
	this->_PSsceneNode->attachObject(this->_particleSystem);

	this->_particleSystem->prepare();
	this->_particleSystem->start();
}
void InnerSkill::update(float elapsed)
{
	ISkill::update(elapsed);
}

void InnerSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;

	this->_particleSystem->stop();
}

void InnerSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
}

void InnerSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	if (name == "Skill_Class02_Inner")
	{
		this->finish();
	}
}

SkillOpcode InnerSkill::getOpcode()
{
	return SkillOpcode::Inner;
}*/