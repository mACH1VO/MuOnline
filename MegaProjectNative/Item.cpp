#pragma  once
#include "StdAfx.h"

#include "Item.h"
#include "MUEnums.h"
#include "ItemData.h"
#include "Storage.h"
#include "Map.h"
#include "GameFramework.h"

#include "TargetMessage.h"
#include "GameClient.h"

#include "GameAttributeUtil.h"
#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"

#include "AAttribute.h"
#include "AttributeI.h"
#include "AttributeF.h"
#include "AttributeB.h"

using namespace Ogre;

namespace Game
{
Item::Item(int sno, int _dynamicId)
	:Actor()
{
	this->dynamicId = _dynamicId;

	//sno = 101;
	string fileName = Storage::getSingletonPtr()->snoMap->at(sno);
	this->itemData = new ItemData();
	this->itemData->Parse(fileName + ".xml");

	this->meshFileName = this->itemData->MeshFileName;
	this->entity = GameFramework::getSingletonPtr()->sceneManager->createEntity("actor_" + Ogre::StringConverter::toString(_dynamicId), this->itemData->MeshFileName);
	this->entity->setUserAny(Ogre::Any((Actor*)this));
	this->entity->setQueryFlags(QueryFlags::ITEM_MASK | QueryFlags::ACTOR_MASK);

	if (this->entity->hasSkeleton())
		this->entity->getSkeleton()->setBlendMode(SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE);

	if (this->itemData->HideMaterialName != "")
	{
		for (int i = 0; i < this->entity->getNumSubEntities(); i++)
		{
			SubEntity* se = this->entity->getSubEntity(i);
			if (se->getMaterialName() == this->itemData->HideMaterialName)
				se->setVisible(false);
		}
	}

	this->_itemLabel = 0;
	this->map = 0;

	Level = 1;
	Defense = 1;
	DefenseRate = 1;
	Durability_Cur = 1;
	Durability_Max = 1;
	Strength_Requeriment = 1;
	Dexterity_Requeriment = 1;
	Vitality_Requeriment = 1;
	Intelligence_Requeriment = 1;
	Level_Requeriment = 1;
}


Item::~Item(void)
{
	Actor::~Actor();
	delete this->itemData;
	GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->entity);
	GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->sceneNode);
	MyGUI::Gui::getInstancePtr()->destroyChildWidget(this->_itemLabel);
}

void Item::enterMap(Vector3 position, Quaternion q, float scale)
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

	std::string itemLabelName = "itemlabel_" + StringConverter::toString(this->dynamicId); 

	this->_itemLabel = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(10,10,100,25), MyGUI::Align::Default, "Overlapped", itemLabelName);
	this->_itemLabel->setVisible(false);
	this->_itemLabel->setCaption(this->itemData->Name);
	this->_itemLabel->setTextAlign(MyGUI::Align::Center);
	this->_itemLabel->eventMouseButtonClick += MyGUI::newDelegate(this, &Item::_itemLabelClicked); // CLASS_POINTER is pointer to CLASS_NAME ('''this''')
	
}

ActorType Item::getActorType()
{
	return ActorType::Item;
}

void Item::update(float timeSinceLastFrame)
{
	Actor::update(timeSinceLastFrame);

	Sphere sphere = this->entity->getWorldBoundingSphere();
	Vector3 sourePoint = this->entity->getParentSceneNode()->getPosition();//sphere.getCenter();

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

		
		//Vector3 location = new Point((int)(result.x * Mu.Instance.Window.Width), (int)(result.y * Mu.Instance.Window.Height));
		if (this->_itemLabel != 0)
		{
			this->_itemLabel->setPosition(pos_x, pos_y);
			if (!this->_itemLabel->getVisible() && this->entity->getVisible())
				this->_itemLabel->setVisible(true);
		}
		
		//throw new Exception("cameraPlane.GetSide(point) != Plane.Side.NEGATIVE_SIDE");
	}

	//////////////////////////////////////
	///////MANUAL FRUSTRUM CULLING!///////
	//////////////////////////////////////

	/*bool shouldBeVisible = false;
	if (GameFramework::getSingletonPtr()->camera->isVisible(this->sceneNode->getPosition()))
		shouldBeVisible = true;

	if (this->entity->getVisible() != shouldBeVisible)
	{
		this->entity->getParentSceneNode()->setVisible(shouldBeVisible);
		this->entity->setVisible(shouldBeVisible);
	}*/
}

void Item::_itemLabelClicked(MyGUI::WidgetPtr _sender)
{
	//AAttribute* aatributes = GameAttributeUtil::getSingletonPtr()->getAttribute((int)AttributeOpcode::Attack);
	//int value = (*this->Attributes)[aatributes];

	Messages::TargetMessage* tm = new Messages::TargetMessage();
	tm->Field0 = 0;
	tm->Field4 = 0;
	tm->Field5 = 0;
	tm->TargetID = this->dynamicId;
	tm->PowerSlot = 0;
	tm->Position = this->getPosition();

	Networking::GameClient* gc = GameFramework::getSingletonPtr()->getGameClient();

	if (gc != 0)
		gc->sendMessage(tm);

	delete tm;
}

void Item::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
	Actor::handleAttributeMessage(message);
	for (int i = 0; i < message->atKeyVals->size(); i++)
	{
		Messages::NetAttributeKeyValue* keyVal = message->atKeyVals->at(i);

		AttributeOpcode attributeOpcode = (AttributeOpcode)keyVal->Index;
		AAttribute* aatribute = (AAttribute*)keyVal->Attribute;

		switch(attributeOpcode)
		{
		case AttributeOpcode::Level:
			{
				this->Level = aatribute->_defaultValue.Value;
				break;
			}
		default:
			{
				LogManager::getSingletonPtr()->logMessage("Could not find attribute " + keyVal->Attribute->Name);
				//OGRE_EXCEPT("Could not find attribute with opcode" + Ogre::StringConverter::toString(keyVal->Index) + "", "");
			}
		}
		LogManager::getSingletonPtr()->logMessage("[Received] " + keyVal->Attribute->Name);
	}
}
}