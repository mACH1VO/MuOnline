#pragma  once
#include "StdAfx.h"

#include "Actor.h"
#include "Player.h"
#include "Equipment.h"
#include "PlayerInventory.h"
#include "InventoryItem.h"
#include "ItemData.h"
#include "Map.h"
#include "MuPath.h"
#include "MUEnums.h"
#include "GameFramework.h"
#include "GameClient.h"
#include "AnimationBlender.h"
#include "AnimationBlender2.h"
#include "StashInventory.h"
#include "ShopInventory.h"
#include "TickTimer.h"
#include "ISkill.h"
#include "SkillFactory.h"
#include "ACDClientTranslateMessage.h"



#include "ButtomBar.h"
#include "StatsPanel.h"
#include "GameGUI.h"

#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"
#include "SkillListMessage.h"
#include "AvailableSkillListMessage.h"

#include "AAttribute.h"
#include "AttributeB.h"
#include "AttributeF.h"
#include "AttributeI.h"
#include "AttributeValue.h"

#include "WingComponent.h"



using namespace Ogre;
namespace Game
{

Player::Player(int sno_id, int _dynamicId, bool _isMainPlayer)
	:Actor()
{
	//Actor::Actor();

	this->dynamicId = _dynamicId;

	this->isMainPlayer = _isMainPlayer;

	this->classType = ClassType::DK;

	this->name = "mach1vo111";

	this->isMoving = false;

	this->meshFileName = "ArmorClass202.mesh";

	this->entity = GameFramework::getSingletonPtr()->sceneManager->createEntity("actor_" + Ogre::StringConverter::toString(_dynamicId), this->meshFileName);
	this->entity->setUserAny(Ogre::Any((Actor*)this));
	this->entity->setQueryFlags(QueryFlags::PLAYER_MASK | QueryFlags::ACTOR_MASK);
	
	//hide the base armor, then create a base armor just like this one
	//in the equipment and treat like gloves, helm, etc
	int num_sub_ent = this->entity->getNumSubEntities();
	this->entity->getSubEntity(0)->setVisible(false); 

	if (this->entity->hasSkeleton())
		this->entity->getSkeleton()->setBlendMode (SkeletonAnimationBlendMode::ANIMBLEND_AVERAGE);

	this->animationBlender = new Utilities::AnimationBlender(this->entity);

	//this->playerSkills = new std::vector<ISkill*>();

	this->currentSkill = 0;
	this->map = 0;

	this->_currentMovementPath = 0;
	this->_currentTranslationPath = 0;

	this->moveSpeed = 45;
	this->translateSpeed = 45;

	this->ChatWidget = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::Widget>("mu_chatlabel", 500, 500, 235, 90, MyGUI::Align::Default, "Main", this->name + "_ChatWidget");
	this->ChatWidgetEditBox = this->ChatWidget->createWidget<MyGUI::EditBox>(MyGUI::WidgetStyle::Child, "EditBoxEmpty", MyGUI::IntCoord(15, 8, 205, 40), MyGUI::Align::Default, "", this->name + "_ChatWidgetEditBox");
	this->ChatWidgetEditBox->setCaption("CHARACTER_BOX");
	this->ChatWidgetEditBox->setTextAlign(MyGUI::Align::Center);
	this->ChatWidgetEditBox->setEditReadOnly(true);
	this->ChatWidgetEditBox->setEditStatic(true);
	this->ChatWidget->setVisible(false);
	this->ChatWidget->setEnabled(false);

	this->ttText = new TickTimer(1000);

	this->isCastingSkill = false;
	this->isTranslating = false;
	this->hasInventoryOpened = false;
	this->hasVaultOpened = false;
	this->hasShopOpened = false;
	this->canWalk = true;

	this->hasHorse = false;
	this->hasWings = false;

	this->wingComponent = new WingComponent(this);
	this->_lastSendedPosition = Vector3::ZERO;

	this->simpleSpline = new Ogre::SimpleSpline();

	this->skillSlots =  new std::map<SkillSlot, SkillOpcode>();
	this->availableSkillSlots = new std::map<unsigned short, SkillOpcode>();

	this->BaseAnimationSpeed = PLAYER_BASE_ANIMATION_SPEED;

	//this->ChatWidgetEditBox = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::EditBox>("mu_chatlabel", 500, 500, 235, 90, MyGUI::Align::Default, "Main", this->name + "_chatlabel");
}


Player::~Player(void)
{
	Actor::~Actor();
}

ActorType Player::getActorType()
{
	return ActorType::Player;
}

Vector3 Player::getPosition()
{
	return Actor::getPosition();
}

void Player::setPosition(Vector3 position)
{
	if ((position - this->_lastSendedPosition).length() > 10)
	{
		int lenn = (position - this->_lastSendedPosition).length();
		Messages::ACDClientTranslateMessage* msg = new Messages::ACDClientTranslateMessage();
		int x = position.x;
		int y = position.y;
		int z = position.z;
		msg->Position = Vector3(position.x, position.y, position.z);
		GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
		delete msg;

		this->_lastSendedPosition = position;
	}
	Actor::setPosition(position);
}

Quaternion Player::getOrientation()
{
	return Actor::getOrientation();
}

void Player::setOrientation(Quaternion quaternion)
{
	Actor::setOrientation(quaternion);
}

void Player::update(float timeSinceLastFrame)
{
	Actor::update(timeSinceLastFrame);

	this->updateMovement(timeSinceLastFrame);
	this->updateTranslation(timeSinceLastFrame);
	this->updateAnimation(timeSinceLastFrame);

	if (this->wingComponent != 0)
		this->wingComponent->update(timeSinceLastFrame);

	if (this->isCastingSkill)
	{
		if (this->currentSkill->isFinished)
		{
			delete this->currentSkill;
			this->isCastingSkill = false;
		}
		else
		{
			this->currentSkill->update(timeSinceLastFrame);
		}
	}

	if (this->inventory != 0)
	{
		this->inventory->update(timeSinceLastFrame);
	}

	if (this->stashInventory != 0)
	{
		this->stashInventory->update(timeSinceLastFrame);
	}

	if (this->shopInventory != 0)
	{
		this->shopInventory->update(timeSinceLastFrame);
	}

	//this->sceneNode->yaw(Ogre::Radian(timeSinceLastFrame));

	/*if (this->playerSkills != 0)
	{
		std::vector<ISkill*>::iterator it;
		for(it = this->playerSkills->begin(); it != this->playerSkills->end(); it++)
		{
			(*it)->update(timeSinceLastFrame);
		}
	}*/

	if (this->isCastingSkill)
	{
		this->currentSkill->update(timeSinceLastFrame);
	}

	if (ttText->TimedOut())
	{
		if (this->ChatWidget->getVisible())
		{
			this->ChatWidgetEditBox->setCaption("");
			this->ChatWidget->setVisible(false);
			this->ChatWidget->setEnabled(false);
		}
	}

	if (this->ChatWidget->getVisible())
	{
		SkeletonInstance* skel = this->entity->getSkeleton();

		Vector3 sourePoint = this->sceneNode->_getFullTransform() * (skel->getBone("Bip01 Ponytail1")->_getDerivedPosition());

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

			pos_x = pos_x - this->ChatWidget->getSize().width/2     + 5;
			pos_y = pos_y - this->ChatWidget->getSize().height      - 10;

			if (this->ChatWidget != 0)
				this->ChatWidget->setPosition(pos_x, pos_y);
		}
	}
}

void Player::say(std::string text, float msTimeOut)
{
	//add some vanish opacity!
	this->ChatWidget->setEnabled(true);
	this->ChatWidget->setVisible(true);
	this->ChatWidgetEditBox->setCaption(text);

	this->ttText->Reset(msTimeOut);
}

void Player::enterMap(Vector3 position, Quaternion q, float scale)
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

	this->inventory = new PlayerInventory(this);
	this->inventory->equipment->createBaseSkinEquipment();

	std::string idle_name = this->selectRightAnimation("Idle");

	this->animationBlender->init(idle_name, true, this);

	this->GeneralCurrentAnimationName = "Idle";

	this->playerState = PlayerState::Idle;

	/*ESTO ESTA MAL, PERO NOSE DONDE PONERLO...*/
	this->stashInventory = new StashInventory(this);
	this->shopInventory = new ShopInventory(this);

	/*this->skillSlots->insert(std::make_pair(SkillSlot::Primary, SkillOpcode::Invalid_Skill));
	this->skillSlots->insert(std::make_pair(SkillSlot::Secondary, SkillOpcode::Invalid_Skill));

	this->skillSlots->insert(std::make_pair(SkillSlot::_one, SkillOpcode::Invalid_Skill));
	this->skillSlots->insert(std::make_pair(SkillSlot::_two, SkillOpcode::Invalid_Skill));
	this->skillSlots->insert(std::make_pair(SkillSlot::_three, SkillOpcode::Invalid_Skill));
	this->skillSlots->insert(std::make_pair(SkillSlot::_four, SkillOpcode::Invalid_Skill));*/

	//this->fillSkillSlots();
	//this->fillAvailableSkillSlots();

	GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->initialize();
}

void Player::fillSkillSlots()
{
	(*this->skillSlots)[SkillSlot::Primary] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::Primary, SkillOpcode::Invalid);

	(*this->skillSlots)[SkillSlot::Secondary] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, SkillOpcode::Invalid);

	(*this->skillSlots)[SkillSlot::_one] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_one, SkillOpcode::Invalid);

	(*this->skillSlots)[SkillSlot::_two] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_two, SkillOpcode::Invalid);

	(*this->skillSlots)[SkillSlot::_three] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_three, SkillOpcode::Invalid);

	(*this->skillSlots)[SkillSlot::_four] = SkillOpcode::Invalid;
	GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_four, SkillOpcode::Invalid);

}

void Player::fillAvailableSkillSlots()
{
	(*this->availableSkillSlots)[0] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[1] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[2] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[3] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[4] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[5] = SkillOpcode::Invalid;
	(*this->availableSkillSlots)[6] = SkillOpcode::Invalid;
}

void Player::MoveTo(Vector3 dest)
{
	if (!this->canWalk)
		return;

	if ((this->getPosition() - dest).length() < 3)
		return;

	if (this->_currentMovementPath != 0)
	{
		delete this->_currentMovementPath;
		this->_currentMovementPath = 0;
	}

	Utilities::MuPath* _path = this->map->FindPath(this->getPosition(), dest);

	if (_path == 0) //_path error
	{
		 this->StopMoving();
	}

	if (_path != 0)
	{
		this->_currentMovementPath = _path;
		this->map->DrawPath(this->_currentMovementPath);
		this->isMoving = true;
		this->playerState = PlayerState::Walking;
		this->PlayAnimation("Walk", true);
	}
}
void Player::TranslateTo(Vector3 dest, float translationSpeed)
{
	this->translateSpeed = translationSpeed;

	if ((this->getPosition() - dest).length() < 3)
		return;

	if (this->_currentTranslationPath != 0)
	{
		delete this->_currentTranslationPath;
		this->_currentTranslationPath = 0;
	}

	Utilities::MuPath* _path = this->map->FindPath(this->getPosition(), dest);

	if (_path == 0) //_path error
	{
		this->StopTranslating();
	}

	if (_path != 0)
	{
		this->_currentTranslationPath = _path;
		this->map->DrawPath(this->_currentTranslationPath);
		this->isTranslating = true;
		//this->playerState = PlayerState::Attacking;
		//this->PlayAnimation("Walk", true);
	}
}
void Player::StopMoving()
{
	this->isMoving = false;
	this->playerState = PlayerState::Idle;

	if ((this->GeneralCurrentAnimationName == "Walk")
		|| (this->GeneralCurrentAnimationName == "Run"))
	{
		this->PlayAnimation("Idle", true);
	}
}

void Player::StopTranslating()
{
	this->isTranslating = false;
	this->playerState = PlayerState::Idle;
}


void Player::PlayAnimation(std::string AnimName, bool loop, BlendingTransition _transition)
{
	if ((AnimName == "Run") && (this->GeneralCurrentAnimationName == "Run") )
		return; // si le doy Run pero estaba en Run, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "Walk") && (this->GeneralCurrentAnimationName == "Walk") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	if ((AnimName == "WeaponSkill") && (this->GeneralCurrentAnimationName == "WeaponSkill") )
		return; // si le doy Walk pero estaba en Walk, salgo porque sino se resetea la animation y queda feo.

	this->GeneralCurrentAnimationName = AnimName;

	String rightAnimName = this->selectRightAnimation(AnimName);
	
	this->animationBlender->blend(rightAnimName, _transition, 0.06, loop);

	//this->isMoving = false;
}
	
void Player::PlaySkill(SkillSlot skillSlot, Actor* _clicked)
{
	SkillOpcode opcode = SkillOpcode::Invalid;

	if (skillSlot == SkillSlot::Primary)
	{
		if (this->skillSlots->count(SkillSlot::Primary))
			opcode = (*this->skillSlots)[SkillSlot::Primary];
	}

	if (skillSlot == SkillSlot::Secondary)
	{
		if (this->skillSlots->count(SkillSlot::Secondary))
			opcode = (*this->skillSlots)[SkillSlot::Secondary];
	}

	if (!this->isCastingSkill)
	{
		ISkill* skill = SkillFactory::getSingletonPtr()->createInstance(this, opcode, _clicked);
		if (skill != 0)
		{
			this->isCastingSkill = true;
			skill->start();
			this->currentSkill = skill;
		}
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage("tryng to cast an skill, but another is in progress!");
	}
}

void Player::PlaySkill(SkillSlot skillSlot, Vector3 _position)
{
	SkillOpcode opcode = SkillOpcode::Invalid;

	if (skillSlot == SkillSlot::Primary)
	{
		if (this->skillSlots->count(SkillSlot::Primary))
			opcode = (*this->skillSlots)[SkillSlot::Primary];
	}

	if (skillSlot == SkillSlot::Secondary)
	{
		if (this->skillSlots->count(SkillSlot::Secondary))
			opcode = (*this->skillSlots)[SkillSlot::Secondary];
	}

	/*if (!this->isCastingSkill)
	{
		ISkill* skill = SkillFactory::getSingletonPtr()->createInstance(this, opcode);
		if (skill != 0)
		{
			this->isCastingSkill = true;
			skill->start();
			this->currentSkill = skill;
		}
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage("tryng to cast an skill, but another is in progress!");
	}*/
}

void Player::updateMovement(float elapsed)
{
	if (!this->isMoving)
		return;

	if (this->_currentMovementPath == 0)
	{
		//LogManager::getSingletonPtr()->logMessage("currentpath == 0 !");
		return;
	}

	Vector3 new_p = this->_currentMovementPath->Advance(elapsed, this->moveSpeed);

	this->setPosition(new_p);

	///update CameraMan
	GameFramework::getSingletonPtr()->cameraMan->updatePlayertracker(new_p);

	this->setDirection(this->_currentMovementPath->CurrDirection);

	if (this->_currentMovementPath->HasReachedPosition())
	{
		this->StopMoving();
	}
}

void Player::updateTranslation(float elapsed)
{
	if (!this->isTranslating)
		return;

	if (this->_currentTranslationPath == 0)
	{
		//LogManager::getSingletonPtr()->logMessage("currentpath == 0 !");
		return;
	}

	Vector3 new_p = this->_currentTranslationPath->Advance(elapsed, this->translateSpeed);

	this->setPosition(new_p);

	///update CameraMan
	GameFramework::getSingletonPtr()->cameraMan->updatePlayertracker(new_p);

	this->setDirection(this->_currentTranslationPath->CurrDirection);

	if (this->_currentTranslationPath->HasReachedPosition())
	{
		this->StopTranslating();
	}
}

void Player::updateAnimation(float elapsed)
{
	this->animationBlender->addTime(elapsed * this->BaseAnimationSpeed);
}


void Player::onAnimationStarted(string name)
{
	if (this->isCastingSkill)
		this->currentSkill->onAnimationStarted(name);
	//LogManager::getSingletonPtr()->logMessage("onAnimationStarted " + name);
}

void Player::onAnimationEnded(string name)
{
	if (this->isCastingSkill)
		this->currentSkill->onAnimationEnded(name);
	//LogManager::getSingletonPtr()->logMessage("onAnimationEnded " + name);
}

void Player::Consume(Messages::GameMessage* message)
{
	switch(message->opcode)
	{
	case Opcodes::SkillListMessage:
		{
			Messages::SkillListMessage* msg = (Messages::SkillListMessage*)message;

			(*this->skillSlots)[SkillSlot::Primary] = msg->Primary;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::Primary, msg->Primary);

			(*this->skillSlots)[SkillSlot::Secondary] = msg->Secondary;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, msg->Secondary);

			(*this->skillSlots)[SkillSlot::_one] = msg->_one;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_one, msg->_one);

			(*this->skillSlots)[SkillSlot::_two] = msg->_two;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_two, msg->_two);

			(*this->skillSlots)[SkillSlot::_three] = msg->_three;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_three, msg->_three);

			(*this->skillSlots)[SkillSlot::_four] = msg->_four;
			GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualSkillIcon(SkillSlot::_four, msg->_four);

			break;
		}
	case Opcodes::AvailableSkillListMessage:
		{
			Messages::AvailableSkillListMessage* msg = (Messages::AvailableSkillListMessage*)message;

			for (int i = 0; i < msg->availableSkillList->size(); i++)
			{
				SkillOpcode skillOpcode = (SkillOpcode)msg->availableSkillList->at(i);
				(*this->availableSkillSlots)[i] = skillOpcode;
				GameFramework::getSingletonPtr()->getGameGUI()->getButtomBar()->setVisualAvailableSkillIcon(i, skillOpcode);
			}
			break;
		}
	default:
		{
			LogManager::getSingletonPtr()->logMessage("Player Consumer could not found the opcode " + Ogre::StringConverter::toString(message->opcode));
			break;
		}
	}
}

std::string Player::selectRightAnimation(std::string animation_name)
{
	if (animation_name == "Walk")
	{
		/*if (this.HasDarkHorse)
			return "Walk_DarkHorse";*/

		if (this->hasWings)
		{
			if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
			{
				InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
				if (iitem != 0)
				{
					if (iitem->itemData->ItemType == "Crossbow")
						return "Walk_Wing_Crossbow";
				}
			}
			return "Walk_Wing";
		}

		if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
		{
			InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
			if (iitem != 0)
			{
				if (iitem->itemData->WalkAnim != "")
					return iitem->itemData->WalkAnim;
			}
		}

		if (this->classType == ClassType::Elf)
		{
			return "Walk_Class03";
		}
		if (this->classType == ClassType::Wizard ||
			this->classType == ClassType::DK ||
			this->classType == ClassType::DL ||
			this->classType == ClassType::MG)
		{
			return "Walk_Class01";
		}
	}

	////////////////////


	if (animation_name == "Idle")
	{
		/*if (this.HasDarkHorse)
			return "Idle_DarkHorse";*/

		if (this->hasWings)
		{
			if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
			{
				InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
				if (iitem != 0)
				{
					if (iitem->itemData->ItemType == "Crossbow")
						return "Idle_Wing_Crossbow";
				}
			}
			return "Idle_Wing";
		}

		if (this->inventory->equipment->VisualWeapon_L != 0)
		{
			if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
			{
				InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
				if (iitem != 0)
				{
					if (iitem->itemData->IdleAnim != "")
						return iitem->itemData->IdleAnim;
				}
			}
		}

		if (this->classType == ClassType::Elf)
		{
			return "Idle1_Class03";
		}

		if (this->classType == ClassType::Wizard ||
			this->classType == ClassType::DK ||
			this->classType == ClassType::DL ||
			this->classType == ClassType::MG)
		{
			return "Idle_Class01";
		}
	}

	if (animation_name == "WeaponSkill")
	{
		if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
		{
			InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
			if (iitem != 0)
			{
				if (iitem->itemData->SkillAnim != "")
					return iitem->itemData->SkillAnim;
			}
		}
	}

	if (animation_name == "Attack")
	{
		if (!this->inventory->equipment->isSlotEmpty(EquipmentSlotId::Weapon_L))
		{
			InventoryItem* iitem = this->inventory->equipment->itemsEquipedBySlot->at(EquipmentSlotId::Weapon_L);
			if (iitem != 0)
			{
				if (iitem->itemData->AttackAnim != "")
					return iitem->itemData->AttackAnim;
			}
		}
	}

	/////////////////////////

	return animation_name;
}

void Player::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
	Actor::handleAttributeMessage(message);
	for (int i = 0; i < message->atKeyVals->size(); i++)
	{
		Messages::NetAttributeKeyValue* keyVal = message->atKeyVals->at(i);

		AttributeOpcode attributeOpcode = (AttributeOpcode)keyVal->Index;
		AAttribute* aatribute = (AAttribute*)keyVal->Attribute;

		switch(attributeOpcode)
		{
		case AttributeOpcode::Hitpoints_Cur:
			{
				this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);
				break;
			}
		case AttributeOpcode::Hitpoints_Max:
			{
				this->Hitpoints_Max = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);
				break;
			}
		case AttributeOpcode::Mana_Cur:
			{
				this->Mana_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Mana_Cur) + "/" + StringConverter::toString(this->Mana_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mmana_EditBox->setCaption(str);
				break;
			}
		case AttributeOpcode::Mana_Max:
			{
				this->Mana_Max = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Mana_Cur) + "/" + StringConverter::toString(this->Mana_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mmana_EditBox->setCaption(str);
				break;
			}
		case AttributeOpcode::Level:
			{
				this->Level = aatribute->_defaultValue.Value;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
				->mlevel_EditBox	->setCaption(Ogre::StringConverter::toString(this->Level));
				break;
			}
		case AttributeOpcode::Strength:
			{
				this->Strength = aatribute->_defaultValue.ValueF;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mstrengh_EditBox->setCaption(StringConverter::toString((int)this->Strength));
				break;
			}
		case AttributeOpcode::Precision:
			{
				this->Agility = aatribute->_defaultValue.ValueF;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->magility_EditBox->setCaption(StringConverter::toString((int)this->Agility));
				break;
			}
		case AttributeOpcode::Vitality:
			{
				this->Stamina = aatribute->_defaultValue.ValueF;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mstamina_EditBox->setCaption(StringConverter::toString((int)this->Stamina));
				break;
			}
		case AttributeOpcode::Intelligence:
			{
				this->Energy = aatribute->_defaultValue.ValueF;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->menergy_EditBox->setCaption(StringConverter::toString((int)this->Energy));
				break;
			}
		case AttributeOpcode::AvailableStatsPoints:
			{
				this->AvailableStatsPoints = aatribute->_defaultValue.Value;
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mavailable_points_number_EditBox
					->setCaption(StringConverter::toString(this->AvailableStatsPoints));
				if (this->AvailableStatsPoints == 0)
				{
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->setEnableAllButtons(false);
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->mavailable_point_text_EditBox->setVisible(false);
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->mavailable_points_number_EditBox->setVisible(false);
				}
				else
				{
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->setEnableAllButtons(true);
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->mavailable_point_text_EditBox->setVisible(true);
					GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()->mavailable_points_number_EditBox->setVisible(true);
				}
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