#pragma  once
#include "StdAfx.h"
#include "NPC.h"
#include "Actor.h"
#include "Player.h"
#include "Equipment.h"
#include "Map.h"
#include "MuPath.h"
#include "MUEnums.h"
#include "GameFramework.h"
#include "AnimationBlender.h"

#include "GameClient.h"
#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"
#include "TargetMessage.h"

#include "NPCData.h"
#include "Storage.h"

using namespace Ogre;

namespace Game
{
NPC::NPC(int sno_id, int _dynamicId)
	:Actor()
{
	//Actor::Actor();

	this->dynamicId = _dynamicId;

	string fileName = Storage::getSingletonPtr()->snoMap->at(sno_id);
	this->Data = new NPCData();
	this->Data->Parse(fileName + ".xml");

	this->meshFileName = this->Data->MeshFileName;
	this->name = this->Data->MeshFileName;

	this->entity = GameFramework::getSingletonPtr()->sceneManager->createEntity("NPC_" + this->meshFileName + Ogre::StringConverter::toString(_dynamicId), this->meshFileName);
	this->entity->setUserAny(Ogre::Any((Actor*)this));
	this->entity->setQueryFlags(QueryFlags::NPC_MASK | QueryFlags::ACTOR_MASK);
	this->entity->setCastShadows(true);

	if (this->entity->hasSkeleton())
		this->entity->getSkeleton()->setBlendMode (SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE);

	this->animationBlender = new Utilities::AnimationBlender(this->entity);

	this->map = 0;

	this->nameEditBox = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::EditBox>("EditBoxEmpty", 500, 500, 150, 20, MyGUI::Align::Default, "Overlapped", this->name + Ogre::StringConverter::toString(this->dynamicId));
	this->nameEditBox->setTextAlign(MyGUI::Align::Center);
	this->nameEditBox->setCaption(this->name);
	this->nameEditBox->setTextShadow(true);
	this->nameEditBox->setVisible(false);
	this->nameEditBox->setEditStatic(true);
	this->nameEditBox->setEditReadOnly(true);
}

NPC::~NPC(void)
{
	Actor::~Actor();
	delete this->animationBlender;
	GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->entity);
	GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->sceneNode);
}

ActorType NPC::getActorType()
{
	return ActorType::NPC;
}

Vector3 NPC::getPosition()
{
	return Actor::getPosition();
}

void NPC::setPosition(Vector3 position)
{
	Actor::setPosition(position);
}

Quaternion NPC::getOrientation()
{
	return Actor::getOrientation();
}

void NPC::setOrientation(Quaternion quaternion)
{
	Actor::setOrientation(quaternion);
}

void NPC::onMouseHover()
{
	Actor::onMouseHover();
	if (this->entity != 0)
	{
		this->entity->setRenderQueueGroup(49);
	}
	MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("mu_npc");
	//this->nameEditBox->setVisible(true);
}

void NPC::onMouseLeave()
{
	Actor::onMouseLeave();
	if (this->entity != 0)
	{
		this->entity->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_MAIN);
	}
	MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("muarrow");
	//this->nameEditBox->setVisible(false);
}

void NPC::onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	//this->entity->setMaterialName("MyMaterial");
	Messages::TargetMessage* tm = new Messages::TargetMessage();
	tm->Field0 = 0;
	tm->Field4 = 0;
	tm->Field5 = 0;
	tm->TargetID = this->dynamicId;
	tm->PowerSlot = 0;
	tm->Position = Vector3::ZERO;

	Networking::GameClient* gc = GameFramework::getSingletonPtr()->getGameClient();

	if (gc != 0)
		gc->sendMessage(tm);

	delete tm;
}

void NPC::update(float timeSinceLastFrame)
{
	Actor::update(timeSinceLastFrame);
	this->updateAnimation(timeSinceLastFrame);

	if (this->isMouseHover)
	{
		SkeletonInstance* skel = this->entity->getSkeleton();

		//Vector3 sourePoint = this->sceneNode->_getFullTransform() * (skel->getBone("Bip01 Ponytail1")->_getDerivedPosition());

		Vector3 sourePoint = this->entity->getWorldBoundingSphere().getCenter();

		Vector2 result = Vector2::ZERO;

		Plane cameraPlane = Plane(GameFramework::getSingletonPtr()->camera->getDerivedOrientation().zAxis(), GameFramework::getSingletonPtr()->camera->getDerivedPosition());

		if (!(cameraPlane.getSide(sourePoint) != Plane::Side::NEGATIVE_SIDE))
		{
			// Transform the 3D point into screen space
			Vector3 temp = GameFramework::getSingletonPtr()->camera->getProjectionMatrix() * (GameFramework::getSingletonPtr()->camera->getViewMatrix() * sourePoint);

			// Transform from coordinate space [-1, 1] to [0, 1] and update in-value
			result.x = (temp.x / 2) + 0.5f;
			result.y = 1 - ((temp.y / 2) + 0.5f);

			int pos_x = (int)(result.x * GameFramework::getSingletonPtr()->Viewport->getActualWidth());
			int pos_y = (int)(result.y * GameFramework::getSingletonPtr()->Viewport->getActualHeight());

			pos_x = pos_x - this->nameEditBox->getSize().width/2     + 0;
			pos_y = pos_y - this->nameEditBox->getSize().height      - 120;

			if (this->nameEditBox != 0)
			{
				if (this->isMouseHover)
				{
					this->nameEditBox->setVisible(true);
					this->nameEditBox->setPosition(pos_x, pos_y);
				}
				else
				{
					this->nameEditBox->setVisible(false);
				}
			}
		}
	}
	else
	{
		this->nameEditBox->setVisible(false);
	}
}

void NPC::enterMap(Vector3 position, Quaternion q, float scale)
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
}

void NPC::PlayAnimation(std::string AnimName, bool loop)
{
	if ((AnimName == "Run") && (this->GeneralCurrentAnimationName == "Run") )
		return; // si le doy Run pero estaba en Run, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "Walk") && (this->GeneralCurrentAnimationName == "Walk") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "WeaponSkill") && (this->GeneralCurrentAnimationName == "WeaponSkill") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	this->GeneralCurrentAnimationName = AnimName;

	String rightAnimName = AnimName/*this->selectRightAnimation(AnimName)*/;

	this->animationBlender->blend(rightAnimName, BlendingTransition::BlendWhileAnimating, 0.06, loop);
}

void NPC::updateAnimation(float elapsed)
{
	this->animationBlender->addTime(elapsed * 0.4);
}

void NPC::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
}
}
