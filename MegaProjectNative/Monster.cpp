#pragma  once
#include "StdAfx.h"
#include "Monster.h"
#include "Actor.h"
#include "Player.h"
#include "Equipment.h"
#include "Map.h"
#include "MuPath.h"
#include "MUEnums.h"
#include "Monster.h"
#include "Storage.h"
#include "MonsterData.h"
#include "GameFramework.h"
#include "AnimationBlender.h"

#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"

using namespace Ogre;

namespace Game
{
Monster::Monster(int sno_id, int _dynamicId)
	:Actor()
{
	//Actor::Actor();

	this->dynamicId = _dynamicId;

	string fileName = Storage::getSingletonPtr()->snoMap->at(sno_id);
	this->monsterData = new MonsterData();
	this->monsterData->Parse(fileName + ".xml");

	this->meshFileName = this->monsterData->MeshFileName;

	this->entity = GameFramework::getSingletonPtr()->sceneManager->createEntity("actor_monster3" + Ogre::StringConverter::toString(_dynamicId), this->meshFileName);
	this->entity->setUserAny(Ogre::Any((Actor*)this));
	this->entity->setQueryFlags(QueryFlags::MONSTER_MASK | QueryFlags::ACTOR_MASK);

	if (this->entity->hasSkeleton())
		this->entity->getSkeleton()->setBlendMode(SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE);


	this->animationBlender = new Utilities::AnimationBlender(this->entity);

	this->map = 0;

	//this->_currentPath = 0;

	this->translateSpeed = 60;
}


Monster::~Monster(void)
{
	Actor::~Actor();
	delete this->animationBlender;
	GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->entity);
	GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->sceneNode);
}

ActorType Monster::getActorType()
{
	return ActorType::Monster;
}

Vector3 Monster::getPosition()
{
	return Actor::getPosition();
}
void Monster::setPosition(Vector3 position)
{
	Actor::setPosition(position);
}

Quaternion Monster::getOrientation()
{
	return Actor::getOrientation();
}
void Monster::setOrientation(Quaternion quaternion)
{
	Actor::setOrientation(quaternion);
}

void Monster::onMouseHover()
{
	Actor::onMouseHover();
	if (this->entity != 0)
	{
		this->entity->setRenderQueueGroup(49);
	}
	MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("mu_attack");
}

void Monster::onMouseLeave()
{
	Actor::onMouseLeave();
	if (this->entity != 0)
	{
		this->entity->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_MAIN);
	}
	MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("muarrow");
}

void Monster::onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	Actor::onMouseClick(evt, id);

	if(id == OIS::MouseButtonID::MB_Left)
	{
		if (GameFramework::getSingletonPtr()->mainPlayer != 0)
		{
			GameFramework::getSingletonPtr()->mainPlayer->PlaySkill(SkillSlot::Primary, this);
		}
	}

	if(id == OIS::MouseButtonID::MB_Right)
	{
		if (GameFramework::getSingletonPtr()->mainPlayer != 0)
		{
			GameFramework::getSingletonPtr()->mainPlayer->PlaySkill(SkillSlot::Secondary, this);
		}
	}
}

void Monster::update(float timeSinceLastFrame)
{
	Actor::update(timeSinceLastFrame);

	this->updateMovement(timeSinceLastFrame);
	this->updateAnimation(timeSinceLastFrame);
	//this->sceneNode->yaw(Ogre::Radian(timeSinceLastFrame));
}

void Monster::enterMap(Vector3 position, Quaternion q, float scale)
{
	Actor::enterMap(position, q, scale);
	this->map = Map::getSingletonPtr();
	std::string sn_name = this->meshFileName + "_" + Ogre::StringConverter::toString(this->dynamicId);
	this->sceneNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode(sn_name);
	this->sceneNode->setPosition(position);
	this->sceneNode->setOrientation(q);
	scale = scale * 0.1f;
	this->sceneNode->setScale(Vector3(scale,scale,scale));

	if (this->entity != 0)
		this->sceneNode->attachObject(this->entity);
	else
		throw "entity should be created!";


	this->animationBlender->init("Idle", true, this);
	this->GeneralCurrentAnimationName = "Idle";
	
	//needs this->entity and this->sceneNode initalized
	//this->equipment = new Equipment(this);

	/*this->equipment->createBaseSkinEquipment();*/

}

void Monster::MoveTo(Vector3 dest)
{
	/*if (this->_currentPath != 0)
	{
		delete this->_currentPath;
		this->_currentPath = 0;
	}

	Utilities::MuPath* _path = this->map->FindPath(this->getPosition(), dest);

	if (_path == 0)
	{
		this->StopMoving();
	}

	if (_path != 0)
	{
		this->_currentPath = _path;
		this->map->DrawPath(this->_currentPath);
		this->isMoving = true;
		this->PlayAnimation("Walk", true);
	}*/
}

void Monster::StopMoving()
{
	this->isMoving = false;

	if ((this->GeneralCurrentAnimationName == "Walk")
		|| (this->GeneralCurrentAnimationName == "Run"))
	{
		this->PlayAnimation("Idle", true);
	}
}

void Monster::PlayAnimation(std::string AnimName, bool loop)
{
	if ((AnimName == "Run") && (this->GeneralCurrentAnimationName == "Run") )
		return; // si le doy Run pero estaba en Run, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "Walk") && (this->GeneralCurrentAnimationName == "Walk") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "WeaponSkill") && (this->GeneralCurrentAnimationName == "WeaponSkill") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	this->GeneralCurrentAnimationName = AnimName;

	String rightAnimName = AnimName/*this->selectRightAnimation(AnimName)*/;

	if (this->animationBlender != 0)
		this->animationBlender->blend(rightAnimName, BlendingTransition::BlendWhileAnimating, 0.06, loop);
}

void Monster::updateMovement(float elapsed)
{
	/*if (!this->isMoving)
		return;

	if (this->_currentPath == 0)
	{
		//LogManager::getSingletonPtr()->logMessage("currentpath == 0 !");
		return;
	}

	Vector3 new_p = this->_currentPath->Advance(elapsed, this->translateSpeed);

	this->setPosition(new_p);

	///update CameraMan
	GameFramework::getSingletonPtr()->cameraMan->updatePlayertracker(new_p);

	this->setDirection(this->_currentPath->CurrDirection);

	if (this->_currentPath->HasReachedPosition())
	{
		this->StopMoving();
	}*/
}

void Monster::updateAnimation(float elapsed)
{
	this->animationBlender->addTime(elapsed * 0.4);
}

void Monster::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
}

}