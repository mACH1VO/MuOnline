#include "StdAfx.h"
#include "TwistingSkill.h"
#include "MUEnums.h"
#include "Player.h"
#include "GameFramework.h"
#include "PlayerInventory.h"
#include "Equipment.h"
#include "InventoryItem.h"


float TwistingSkill::frequency = 5;
float TwistingSkill::Amplitude = 10;
float TwistingSkill::phase = 0;

TwistingSkill::TwistingSkill(Game::Player* _owner)
	:ISkill(_owner, 5000)
{
	this->_sceneNode = 0;
	this->_PSsceneNode = 0;
	this->_entity = 0;
	//this->_particleSystem = 0;

	TwistingSkill::frequency = 5;
	TwistingSkill::Amplitude = 10;
	TwistingSkill::phase = 0;
}


TwistingSkill::~TwistingSkill(void)
{
	if (this->_entity != 0)
		GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->_entity);

	if (this->_sceneNode != 0)
		GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->_sceneNode);

	/*if (this->_PSsceneNode != 0)
	{
		this->_particleSystem->stop();
		this->_PSsceneNode->detachObject(this->_particleSystem);
		std::string psName = this->_particleSystem->getName();

		ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyParticleSystem(this->_particleSystem, GameFramework::getSingletonPtr()->sceneManager);
		GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->_PSsceneNode);
	}*/
}


void TwistingSkill::start()
{
	ISkill::start();
	Ogre::LogManager::getSingletonPtr()->logMessage("TwistingSkill::start()");
	this->owner->PlayAnimation("Skill_Class02_Twisting", false);

	AnimationState* animState = this->owner->entity->getAnimationState("Skill_Class02_Twisting");
	float len = animState->getLength();

	TwistingSkill::frequency = (Ogre::Math::TWO_PI) / len; // FORCE ONE TWIST SYNC WITH ANIM LEN

	this->_sceneNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
	if (this->owner->inventory->equipment->VisualWeapon_L != 0)
	{
		string name = this->owner->inventory->equipment->VisualWeapon_L->getName();
		this->_entity = this->owner->inventory->equipment->VisualWeapon_L->clone(name + "_twisting_clone");
		this->_sceneNode->attachObject(this->_entity);
		this->_sceneNode->setScale(Vector3::UNIT_SCALE * 0.1);
	}
	this->owner->canWalk = false;

	//Deathstab

	/*this->_PSsceneNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
	this->_PSsceneNode->setPosition(this->owner->getPosition());
	ParticleUniverse::ParticleSystemManager* pManager =	ParticleUniverse::ParticleSystemManager::getSingletonPtr();

	std::string ps_name = "Twisting_ps_" + Ogre::StringConverter::toString(this->owner->dynamicId);
	this->_particleSystem = pManager->createParticleSystem(ps_name, "Deathstab", GameFramework::getSingletonPtr()->sceneManager);

	this->_PSsceneNode->attachObject(this->_particleSystem);
	//pSys->setScale(Vector3::UNIT_SCALE * 5);
	//mNode->setScale(10, 10, 10);

	this->_particleSystem->prepare();
	this->_particleSystem->start();*/
}

void TwistingSkill::update(float elapsed)
{
	ISkill::update(elapsed);

	if (this->_sceneNode != 0)
	{
		Vector3 center = this->owner->getPosition();

		//LogManager::getSingletonPtr()->logMessage("sec_elapsed " + Ogre::StringConverter::toString(this->secondsElapsed));

		float factor_used_in_animation = 0.2;
		float x = Amplitude * Ogre::Math::Cos(Ogre::Radian(this->secondsElapsed * frequency * factor_used_in_animation + phase));
		float z = Amplitude * Ogre::Math::Sin(Ogre::Radian(this->secondsElapsed * frequency * factor_used_in_animation + phase));
		float y = 10;

		Vector3 offset = Vector3(x, y, z);

		this->_sceneNode->setPosition(center + offset);
	}

	/*AnimationState* animState = this->owner->entity->getAnimationState("Skill_Class02_Twisting");
	float percent_executed = animState->getTimePosition() / animState->getLength();
	if (percent_executed > 0.9)
	{
		this->finish();
	}*/
}

void TwistingSkill::finish()
{
	ISkill::finish();
	this->owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
	this->owner->canWalk = true;
	//Ogre::LogManager::getSingletonPtr()->logMessage("TwistingSkill::finish()");
}

void TwistingSkill::onAnimationStarted(string name)
{
	ISkill::onAnimationStarted(name);
	//LogManager::getSingletonPtr()->logMessage("TwistingSkill::onAnimationStarted " + name);
}

void TwistingSkill::onAnimationEnded(string name)
{
	ISkill::onAnimationEnded(name);
	//LogManager::getSingletonPtr()->logMessage("TwistingSkill::onAnimationEnded " + name);
	if (name == "Skill_Class02_Twisting")
	{
		this->finish();
	}
}

SkillOpcode TwistingSkill::getOpcode()
{
	return SkillOpcode::Twisting;

}