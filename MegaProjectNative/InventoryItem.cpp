#include "StdAfx.h"
#include "InventoryItem.h"
#include "ItemData.h"
#include "Storage.h"
#include "GameGUI.h"
#include "BaseInventory.h"
#include "PlayerInventory.h"
#include "GameFramework.h"
#include "Equipment.h"
#include "InventoryPanel.h"
#include "ShopPanel.h"
#include "TooltipItem.h"
#include "StashPanel.h"

#include "IAttributable.h"
#include "AAttribute.h"
#include "AttributeB.h"
#include "AttributeF.h"
#include "AttributeI.h"

#include "StashInventory.h"
#include "TooltipItem.h"
#include "Player.h"
#include "Item.h"
#include "MUEnums.h"

#include "GameClient.h"

#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"

#include "InventoryRequestBuyItemMessage.h"
#include "InventoryRequestSellItemMessage.h"

#include "InventoryRequestMoveMessage.h"
#include "InventoryResponseMoveMessage.h"
#include "InventoryDropItemMessage.h"
#include "InventoryRequestJewelUse.h"

#include "TransformInventoryUtil.h"

namespace Game
{
InventoryItem::InventoryItem(int _dynamicId, int _sno, InventorySlot* _invSlot, BaseInventory* _inventory)
	:IAttributable()
{
	this->dynamicId = _dynamicId;
	this->isOnAir = false;
	this->isMouseHover = false;
	this->offsetPoint = Vector2::ZERO;
	this->rotationAxis = RotationAxis::yaw__y;

	string fileName = Storage::getSingletonPtr()->snoMap->at(_sno);
	this->itemData = new ItemData();
	this->itemData->Parse(fileName + ".xml");
	this->offsetPoint = this->itemData->OffsetPoint;

	this->baseInventory = _inventory;
	this->inventorySize = this->itemData->inventorySize; //VALGA LA REDUNDANCIA...
	this->inventorySlot = new Game::InventorySlot(0,0);
	this->inventorySlot->R = _invSlot->R;
	this->inventorySlot->C = _invSlot->C;

	//this->meshFileName = this->itemData->MeshFileName;
	this->entity = GameFramework::getSingletonPtr()->sceneManager->createEntity(this->itemData->MeshFileName);
	this->entity->setCastShadows(false);
	this->sceneNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
	this->sceneNode->attachObject(this->entity);

	//this->entity->setRenderQueueGroup(RENDER_QUEUE_INVENTORY_ITEM);
	this->entity->setRenderQueueGroup(RENDER_QUEUE_INVENTORY_ITEM);
	//this->entity->setRenderQueueGroupAndPriority(RenderQueueGroupID::RENDER_QUEUE_OVERLAY, 0);

	//this->entity->getMesh()->_setBoundingSphereRadius(999999);

	//this->entity->getMesh()->_setBounds(Ogre::AxisAlignedBox(Ogre::AxisAlignedBox::EXTENT_INFINITE));

	this->sceneNode->setPosition(Vector3::ZERO);
	this->sceneNode->setScale(Vector3::UNIT_SCALE * this->itemData->BaseScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);

	this->_waiting_for_request_response = false;
	this->equipmentSlot = EquipmentSlotId::_Inventory;

	this->widget = 0;

	this->isStatic = false;


	if (this->itemData->ItemType == "Axe_1H" || this->itemData->ItemType == "Axe_2H")
	{
		this->sceneNode->pitch(Ogre::Degree(-90));
		this->sceneNode->roll(Ogre::Degree(-90));
		this->sceneNode->pitch(Ogre::Degree(10));
		this->offsetPoint = Vector2(5, 20);
		this->rotationAxis = RotationAxis::roll__z;
	}

	if (this->itemData->ItemType == "Mace_2H")
	{
		this->sceneNode->pitch(Ogre::Degree(-90));
		this->sceneNode->roll(Ogre::Degree(-90));
		this->sceneNode->pitch(Ogre::Degree(20));
		this->offsetPoint = Vector2(5, 20);
		this->rotationAxis = RotationAxis::roll__z;
	}

	if (this->itemData->ItemType == "Mace_1H")
	{
		this->sceneNode->pitch(Ogre::Degree(-90));
		this->sceneNode->roll(Ogre::Degree(-90));
		//this->sceneNode->pitch(Ogre::Degree(20));
		this->offsetPoint = Vector2(5, 20);
		this->rotationAxis = RotationAxis::roll__z;
	}

	if (this->itemData->ItemType == "Crossbow")
	{
		this->sceneNode->roll(Ogre::Degree(-170));
		this->rotationAxis = RotationAxis::yaw__y;
	}

	if (this->itemData->ItemType == "Bow")
	{
		this->sceneNode->yaw(Ogre::Degree(-90));
		this->sceneNode->pitch(Ogre::Degree(-70));
		this->rotationAxis = RotationAxis::roll__z;
	}

	if (this->itemData->HideMaterialName != "")
	{
		for (int i = 0; i < this->entity->getNumSubEntities(); i++)
		{
			SubEntity* se = this->entity->getSubEntity(i);
			string mat_name = se->getMaterialName();
			if (mat_name == this->itemData->HideMaterialName)
				se->setVisible(false);
		}
	}

	this->_initial_orientation = this->sceneNode->getOrientation();
	
	/*Ogre::Entity* actualOutlineGlowEntity = this->entity->clone(this->entity->getName() + "_glow");
	actualOutlineGlowEntity->getMesh()->_setBounds(Ogre::AxisAlignedBox(Ogre::AxisAlignedBox::EXTENT_INFINITE));
	actualOutlineGlowEntity->setRenderQueueGroup(RENDER_QUEUE_INVENTORY_ITEM_GLOW);
	actualOutlineGlowEntity->setMaterialName("cg/glow");
	Ogre::SceneNode* actualOutlineGlowNode = this->entity->getParentSceneNode()->createChildSceneNode(this->sceneNode->getName() + "_GlowNode");
	actualOutlineGlowNode->attachObject(actualOutlineGlowEntity); */

	Level = 0;
	Defense = 0;
	DefenseRate = 0;
	Durability_Cur = 0;
	Durability_Max = 0;
	Strength_Requeriment = 0;
	Dexterity_Requeriment = 0;
	Vitality_Requeriment = 0;
	Intelligence_Requeriment = 0;
	Level_Requeriment = 0;
	Damage_Weapon_Max = 0;
	Damage_Weapon_Min = 0;
	Speed = 0;
	Skill = 0;
}

InventoryItem::~InventoryItem(void)
{
	//IAttributable::~IAttributable();
	this->isMouseHover = false;
	this->isOnAir = false;

	delete itemData;
	delete inventorySlot;
	//delete inventorySize; this is deleted in itemData!
	GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->entity);
	GameFramework::getSingletonPtr()->sceneManager->destroySceneNode(this->sceneNode);

	if (this->widget != 0)
	{
		MyGUI::Gui::getInstancePtr()->destroyWidget(this->widget);
	}


	this->widget = 0;
}

void InventoryItem::createWidgetandSetUpCallbacks()
{
	int _width = this->itemData->inventorySize->Width * 32;
	int _height = this->itemData->inventorySize->Height * 32;

	this->widget = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::Widget>(/*"Button"*/"mu_chat_background", MyGUI::IntCoord(0,0,_width,_height), MyGUI::Align::Default, "Popup", StringConverter::toString(this->dynamicId));
	this->widget->setColour(MyGUI::Colour::White);

	this->widget->eventChangeCoord += MyGUI::newDelegate(this, &InventoryItem::eventChangeCoord);
	this->widget->eventMouseSetFocus += MyGUI::newDelegate(this, &InventoryItem::eventMouseSetFocus);
	this->widget->eventMouseLostFocus += MyGUI::newDelegate(this, &InventoryItem::eventMouseLostFocus);
	this->widget->eventMouseButtonClick += MyGUI::newDelegate(this, &InventoryItem::eventMouseButtonClick);
	MyGUI::Widget* slot_wid = 0;

	if(this->baseInventory->getInventoryWindowsID() == InventoryWindowsID::_PlayerInventory)
	{
		slot_wid = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel()->getWidgetSlotByRC(this->inventorySlot->R, this->inventorySlot->C);
	}
	else if (this->baseInventory->getInventoryWindowsID() == InventoryWindowsID::_SHOP)
	{
		slot_wid = GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel()->getWidgetSlotByRC(this->inventorySlot->R, this->inventorySlot->C);
	}
	else if (this->baseInventory->getInventoryWindowsID() == InventoryWindowsID::Vault)
	{
		slot_wid = GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel()->getWidgetSlotByRC(this->inventorySlot->R, this->inventorySlot->C);
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage("[ERROR] IN createWidgetandSetUpCallbacks(), COULD NOT FIND getInventoryWindowsID");
	}


	this->widget->setPosition(slot_wid->getAbsolutePosition());
	this->widget->setAlpha(0.5);

	MyGUI::IntSize _size = this->widget->getSize();
	int new_x = this->widget->getAbsolutePosition().left + (_size.width/2);
	int new_y = this->widget->getAbsolutePosition().top + (_size.height/2);

	Vector3 final_position = this->getRealInventoryEntityPosition(new_x, new_y);
	this->_last_XY_sceneNode_setPosition = Vector2(new_x, new_y);
	this->sceneNode->setPosition(final_position);
	this->sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * this->itemData->BaseScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);

}

void InventoryItem::eventChangeCoord(MyGUI::WidgetPtr _sender)
{
	//this->setToolTipRightPosition();

	/*if (this->isOnAir) //little trick!
		this->toolTip->setVisible(false);*/

	//LogManager::getSingletonPtr()->logMessage("eventChangeCoord");
}

void InventoryItem::eventMouseButtonRightClick()
{
	//LogManager::getSingletonPtr()->logMessage("InventoryItem RIGHT CLICKED!");
	
	//currentInventoryItemHovered
	if (GameFramework::getSingletonPtr()->itemOnAir != 0)
		if (GameFramework::getSingletonPtr()->itemOnAir->dynamicId == this->dynamicId)
			return;

	//check for shop (to sell)
	if (GameFramework::getSingletonPtr()->mainPlayer->inventory->hasItem(this->dynamicId))
	{
		if (GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel()->getMainWidget()->getVisible())
		{
			ShopPanel* shopPanel = GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel();
			//now, lets send SELL request!
			Messages::InventoryRequestSellItemMessage* msg = new Messages::InventoryRequestSellItemMessage();
			msg->DynamicID = this->dynamicId;
			GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
			delete msg;
		}
	}

	//check for vault, send quickmove
	if (GameFramework::getSingletonPtr()->mainPlayer->inventory->hasItem(this->dynamicId))
	{
		if (GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel()->getMainWidget()->getVisible())
		{
			/*ShopPanel* shopPanel = GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel();
			//now, lets send SELL request!
			Messages::InventoryRequestSellItemMessage* msg = new Messages::InventoryRequestSellItemMessage();
			msg->DynamicID = this->dynamicId;
			GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
			delete msg;*/
		}
	}


	//GameFramework::getSingletonPtr()->getGameGUI()->_temp_itemwidget_for_right_click = 0;
}

void InventoryItem::eventMouseButtonClick(MyGUI::WidgetPtr _sender)
{
	if (this->isStatic)
	{
		LogManager::getSingletonPtr()->logMessage("Clicked static inventoryItem!");
		if (this->baseInventory->getInventoryWindowsID() == InventoryWindowsID::_SHOP)
		{
			Messages::InventoryRequestBuyItemMessage* msg_req = new Messages::InventoryRequestBuyItemMessage();
			msg_req->DynamicID = this->dynamicId;
			GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg_req);
			delete msg_req;
		}
		return;
	}

	if (GameFramework::getSingletonPtr()->itemOnAir == 0)
	{
		//put in air
		this->isOnAir = true;
		GameFramework::getSingletonPtr()->itemOnAir = this;
		this->sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * this->itemData->HoverScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);

		MyGUI::PointerManager::getInstancePtr()->setVisible(false);
		//GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(false);
		//this->toolTip->setVisible(false);
	}
	else
	{
		InventoryItem* _itemOnair = GameFramework::getSingletonPtr()->itemOnAir;
		//_itemOnair should be this!
		InventoryPanel* inventoryPanel = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel();

		//now, detect where the request is gonna be, equipment, inv grid, npc, vault etc...
		MyGUI::Widget* inv_slot_widget = inventoryPanel->getWidgetSlotByScreenPosition_modified(this->widget->getAbsolutePosition());
		if (inv_slot_widget != 0)
		{
			//inventory grid destination!
			InventoryPanel* inventoryPanel = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel();
			InventorySlot slot = inventoryPanel->getSlotByWidgetName(inv_slot_widget->getName());

			if (this->baseInventory->canPutitemThere_checking_self_item(slot, *this->inventorySize, this->dynamicId))
			{
				//request move!
				this->_waiting_for_request_response = true;
				Messages::InventoryRequestMoveMessage* msg = new Messages::InventoryRequestMoveMessage();
				msg->EquipmentSlot = (int)EquipmentSlotId::_Inventory;
				msg->ItemID = this->dynamicId;
				msg->inventoryWindowId = (int)InventoryWindowsID::_PlayerInventory;
				msg->Row = slot.R;
				msg->Column = slot.C;
				GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
				delete msg;
			}
			else
			{
				//IF THIS IS JEWEL, SEN MODE REQUEST ANYWAY, SO SERVER BLESS ITEM!
				if (this->itemData->ItemType == "Jewel")
				{
					//dest item id!
					Messages::InventoryRequestJewelUse* msg = new Messages::InventoryRequestJewelUse();
					msg->sourceJewelId = this->dynamicId;
					msg->destItemId = this->baseInventory->getItemIdBySlot(slot);
					GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
					delete msg;
				}
				else
				{
					LogManager::getSingletonPtr()->logMessage("canot put item there! client checked!");
				}
			}
		}
		else
		{
			LogManager::getSingletonPtr()->logMessage("[InventoryItem, clickevent] inv_slot_widget == 0");
		}


		//check for equipment slots!
		MyGUI::types::TPoint<int> center_widget_position = this->widget->getAbsolutePosition();
		center_widget_position = center_widget_position + MyGUI::types::TPoint<int>(this->widget->getSize().width / 2, this->widget->getSize().height / 2);
		MyGUI::Widget* equipmentWidget = inventoryPanel->getEquipmentWidgetByScreenPosition(center_widget_position);
		if (equipmentWidget != 0)
		{
			std::string equi_wid_name = equipmentWidget->getName();
			EquipmentSlotId equipment_id = inventoryPanel->getEquipmentIdByWidgetName(equi_wid_name);

			if ( ((PlayerInventory*)this->baseInventory)->equipment->isSlotEmpty(equipment_id) )
			{
				this->_waiting_for_request_response = true;
				Messages::InventoryRequestMoveMessage* msg = new Messages::InventoryRequestMoveMessage();
				msg->EquipmentSlot = equipment_id; //requested slot!
				msg->ItemID = this->dynamicId;
				msg->inventoryWindowId = (int)InventoryWindowsID::_PlayerInventory;
				msg->Row = 0;
				msg->Column = 0;
				GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
				delete msg;
			}
		}


		//check for vault!
		if (GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel()->getMainWidget()->getVisible())
		{
			StashPanel* stashPanel = GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel();
			MyGUI::Widget* stash_slot_widget = stashPanel->getWidgetSlotByScreenPosition_modified(this->widget->getAbsolutePosition());
			if (stash_slot_widget != 0)
			{
				//inventory grid destination
				std::string namee = stash_slot_widget->getName();
				InventorySlot slot_stash = stashPanel->getSlotByWidgetName(namee);
				StashInventory* stashInventory = GameFramework::getSingletonPtr()->mainPlayer->stashInventory;
				if (stashInventory->canPutitemThere_checking_self_item(slot_stash, *this->inventorySize, this->dynamicId))
				{
					//request move!
					this->_waiting_for_request_response = true;
					Messages::InventoryRequestMoveMessage* msg = new Messages::InventoryRequestMoveMessage();
					msg->EquipmentSlot = (int)EquipmentSlotId::_Inventory;
					msg->ItemID = this->dynamicId;
					msg->inventoryWindowId = (int)InventoryWindowsID::Vault;
					msg->Row = slot_stash.R;
					msg->Column = slot_stash.C;
					GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
					delete msg;
				}
				else
				{
					LogManager::getSingletonPtr()->logMessage("(check for vault!) canot put item there! client checked!");
				}
			}
		}

		//check for shop (to sell)
		if (GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel()->getMainWidget()->getVisible())
		{
			ShopPanel* shopPanel = GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel();
			MyGUI::Widget* shop_slot_widget = shopPanel->getWidgetSlotByScreenPosition_modified(this->widget->getAbsolutePosition());
			if (shop_slot_widget != 0)
			{
				//now, lets send SELL request!
				Messages::InventoryRequestSellItemMessage* msg = new Messages::InventoryRequestSellItemMessage();
				msg->DynamicID = this->dynamicId;
				GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
				delete msg;
			}
		}


		//ok, if item's corner is not hovering any inv slots or any equipment, check if it's hovering any gui, if not, drop!
		int x = this->widget->getAbsolutePosition().left - 10;
		int y = this->widget->getAbsolutePosition().top - 10;
		bool isHoveringAnyWidget = (MyGUI::LayerManager::getInstancePtr()->getWidgetFromPoint(x,y) != 0);
		if (!isHoveringAnyWidget)
		{
			//send Drop request!
			Messages::InventoryDropItemMessage dropmsg;
			dropmsg.ItemID = this->dynamicId;
			GameFramework::getSingletonPtr()->getGameClient()->sendMessage(&dropmsg);

			//LogManager::getSingletonPtr()->logMessage("Drop request sent!");
		}
	}

	LogManager::getSingletonPtr()->logMessage("eventMouseButtonClick");
}

void InventoryItem::acceptItemMovement(Messages::InventoryResponseMoveMessage* msg, InventoryWindowsID dest_window_id)
{
	if (this->isOnAir) //siempre deberia esta en air, no?
	{
		this->isOnAir = false;
		GameFramework::getSingletonPtr()->itemOnAir = 0;

		MyGUI::PointerManager::getInstancePtr()->setVisible(true);
		//GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(true);

		MyGUI::Widget* dest_wid = 0;

		InventoryPanel* inventoryPanel = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel();
		StashPanel* stashPanel = GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel();

		if (dest_window_id == InventoryWindowsID::_PlayerInventory)
		{
			if (msg->EquipmentSlot == EquipmentSlotId::_Inventory)
			{
				//To Inventory!
				dest_wid = inventoryPanel->getWidgetSlotByRC(msg->Row, msg->Column);

				this->widget->setPosition(dest_wid->getAbsolutePosition());

				//set entity in middle button
				MyGUI::IntSize _size = this->widget->getSize();
				int new_x = this->widget->getAbsolutePosition().left + (_size.width/2);
				int new_y = this->widget->getAbsolutePosition().top + (_size.height/2);


				Vector3 final_position = this->getRealInventoryEntityPosition(new_x, new_y);
				this->_last_XY_sceneNode_setPosition = Vector2(new_x, new_y);
				this->sceneNode->setPosition(final_position);
				this->sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * this->itemData->BaseScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);
				this->widget->setAlpha(0.5);
			}
			else
			{
				//To Equipment!
				dest_wid = inventoryPanel->getWidgetByEquipmentId((EquipmentSlotId)msg->EquipmentSlot);

				MyGUI::IntPoint _dest_widget_abspos = dest_wid->getAbsolutePosition();
				MyGUI::IntSize _dest_widget_size = dest_wid->getSize();
				MyGUI::IntPoint _dest_widget_rectangle_center = _dest_widget_abspos + MyGUI::IntPoint(_dest_widget_size.width/2, _dest_widget_size.height/2);

				this->widget->setPosition(dest_wid->getAbsolutePosition()); //first, need to put the inv_item_wid exactly in that point!

				MyGUI::IntPoint _item_widget_abspos = this->widget->getAbsolutePosition();
				MyGUI::IntSize _item_widget_size = this->widget->getSize();
				MyGUI::IntPoint _item_widget_rectangle_center = _item_widget_abspos + MyGUI::IntPoint(_item_widget_size.width/2, _item_widget_size.height/2);

				MyGUI::IntPoint final_position_for_equipment = _dest_widget_abspos + (_dest_widget_rectangle_center - _item_widget_rectangle_center);

				this->widget->setPosition(final_position_for_equipment);

				//set entity in middle button
				MyGUI::IntSize _size = this->widget->getSize();
				int new_x = final_position_for_equipment.left + (_size.width/2);
				int new_y = final_position_for_equipment.top + (_size.height/2);

				Vector3 final_position = this->getRealInventoryEntityPosition(new_x, new_y);
				this->_last_XY_sceneNode_setPosition = Vector2(new_x, new_y);
				this->sceneNode->setPosition(final_position);
				this->sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * this->itemData->BaseScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);
			
				this->widget->setAlpha(0);
			}
		}

		if (dest_window_id == InventoryWindowsID::Vault)
		{
			dest_wid = stashPanel->getWidgetSlotByRC(msg->Row, msg->Column);

			this->widget->setPosition(dest_wid->getAbsolutePosition());

			//set entity in middle button
			MyGUI::IntSize _size = this->widget->getSize();
			int new_x = this->widget->getAbsolutePosition().left + (_size.width/2);
			int new_y = this->widget->getAbsolutePosition().top + (_size.height/2);


			Vector3 final_position = this->getRealInventoryEntityPosition(new_x, new_y);
			this->_last_XY_sceneNode_setPosition = Vector2(new_x, new_y);
			this->sceneNode->setPosition(final_position);
			this->sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * this->itemData->BaseScale3D / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION);
			this->widget->setAlpha(0.5);
		}
		
		this->_waiting_for_request_response = false;

		this->setToolTipRightPosition();
		GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(true);
		
		//NO HACER ESTO ACA, NO CORRESPONDE!
		/*this->inventorySlot->R = msg->Row;
		this->inventorySlot->C = msg->Column;*/
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage(LogMessageLevel::LML_CRITICAL, "[InventoryItem] acceptItemMovement error, item is not in air!");
	}
}

void InventoryItem::eventMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old)
{
	this->isMouseHover = true;
	GameFramework::getSingletonPtr()->currentInventoryItemHovered = this;
	LogManager::getSingletonPtr()->logMessage("eventMouseSetFocus");

	GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(true);
	this->setToolTipRightPosition();
	this->fillTooltipData();
}

void InventoryItem::eventMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old)
{
	this->isMouseHover = false;
	GameFramework::getSingletonPtr()->currentInventoryItemHovered = 0;
	LogManager::getSingletonPtr()->logMessage("eventMouseLostFocus");

	GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(false);
	//this->toolTip->setVisible(false);
}

void InventoryItem::update(float timeSinceLastFrame)
{
	if(this->widget != 0)
	{
		if (!this->widget->getVisible())
			return;

		if (this->isOnAir)
		{
			if (GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->getVisible())
				GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget()->setVisible(false);
		}

		if (this->sceneNode != 0)
		{
			if (this->isMouseHover)
			{
				if (this->rotationAxis == RotationAxis::yaw__y)
					this->sceneNode->yaw(Ogre::Radian(timeSinceLastFrame) * 10);

				if (this->rotationAxis == RotationAxis::pitch__x)
					this->sceneNode->pitch(Ogre::Radian(timeSinceLastFrame) * 10);

				if (this->rotationAxis == RotationAxis::roll__z)
					this->sceneNode->roll(Ogre::Radian(timeSinceLastFrame) * 10);
			}
			else
			{
				this->sceneNode->setOrientation(this->_initial_orientation);
			}

			if ((this->isOnAir) && (!this->_waiting_for_request_response))
			{
				int x = GameFramework::getSingletonPtr()->lastMouseX;
				int y = GameFramework::getSingletonPtr()->lastMouseY;

				MyGUI::IntSize _size = this->widget->getSize();
				int new_x_corner = x - (_size.width/2);
				int new_y_corner = y - (_size.height/2);

				//when moving the cursor and items is on air, button is shifter to the top left by size/2!
				this->widget->setPosition(new_x_corner, new_y_corner); 

				Vector3 final_position = this->getRealInventoryEntityPosition(x, y);
				this->_last_XY_sceneNode_setPosition = Vector2(x, y);
				this->sceneNode->setPosition(final_position);

				InventoryPanel* inventoryPanel = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel();

				inventoryPanel->setAllSlotsColor(MyGUI::Colour::White);
				inventoryPanel->setAllEquipmentColour(MyGUI::Colour::White);

				MyGUI::Widget* slot_wid = inventoryPanel->getWidgetSlotByScreenPosition_modified(this->widget->getAbsolutePosition());
				if (slot_wid != 0)
				{
					InventorySlot slot = inventoryPanel->getSlotByWidgetName(slot_wid->getName());
					inventoryPanel->setHoverSlotsColor(&slot, this->inventorySize, MyGUI::Colour(0.7,0.7,0.7));
				}
				else
				{
					//if item widget is not hovering inventorySlots, check for equipment!
					inventoryPanel->setHoverSlotsColor(this->widget->getAbsoluteRect(), MyGUI::Colour::Red);

					//esto del center es solo para equipment! center_widget_position para chequear si esta hover el equip slot!
					MyGUI::types::TPoint<int> center_widget_position = this->widget->getAbsolutePosition();
					center_widget_position = center_widget_position + MyGUI::types::TPoint<int>(this->widget->getSize().width / 2, this->widget->getSize().height / 2);
					MyGUI::Widget* equipmentWidget = inventoryPanel->getEquipmentWidgetByScreenPosition(center_widget_position);
					if (equipmentWidget != 0)
					{
						equipmentWidget->setColour(MyGUI::Colour(0.7,0.7,0.7));
					}
				}
				//inventoryPanel->setHoverSlotsColor(this->widget->getAbsoluteRect(), MyGUI::Colour::Black);


				//now, apart from all that before, do checks for vault!
				StashPanel* stashPanel = GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel();
				if (stashPanel->getMainWidget()->getVisible())
				{
					stashPanel->setAllSlotsColor(MyGUI::Colour::White);

					MyGUI::Widget* slot_vault_wid = stashPanel->getWidgetSlotByScreenPosition_modified(this->widget->getAbsolutePosition());
					if (slot_vault_wid != 0)
					{
						InventorySlot slot = stashPanel->getSlotByWidgetName(slot_vault_wid->getName());
						stashPanel->setHoverSlotsColor(&slot, this->inventorySize, MyGUI::Colour(0.7,0.7,0.7));
					}
				}
				
			}
		}
	}
}

void InventoryItem::setToolTipRightPosition()
{
	MyGUI::Widget* tooltip = GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem()->getMainWidget();
	MyGUI::types::TRect<int> abs_rect_ = tooltip->getAbsoluteRect();
	MyGUI::types::TPoint<int> offset(-50, -tooltip->getSize().height);
	tooltip->setPosition(this->widget->getPosition() + offset);

	
}

void InventoryItem::fillTooltipData()
{
	TooltipItem* tooltipItem = GameFramework::getSingletonPtr()->getGameGUI()->getTooltipItem();
	//tooltipItem->getMainWidget()->setRenderItemTexture();
	//clean everything!
	tooltipItem->mitem_name_EditBox->setCaption("");
	tooltipItem->mattribute_0_EditBox->setCaption("");
	tooltipItem->mattribute_1_EditBox->setCaption("");
	tooltipItem->mattribute_2_EditBox->setCaption("");
	tooltipItem->mattribute_3_EditBox->setCaption("");
	tooltipItem->mattribute_4_EditBox->setCaption("");
	tooltipItem->mattribute_5_EditBox->setCaption("");
	tooltipItem->mattribute_6_EditBox->setCaption("");
	tooltipItem->mattribute_7_EditBox->setCaption("");

	//now, fill data
	string fullname = "ItemName + " + Ogre::StringConverter::toString(this->Level);
	string color = "#eeee00";
	fullname = color + fullname;
	tooltipItem->mitem_name_EditBox->setCaption(fullname);

	bool isSetItem = (this->itemData->ItemType == "Helm") 
		|| (this->itemData->ItemType == "Armor")
		|| (this->itemData->ItemType == "Pants")
		|| (this->itemData->ItemType == "Gloves")
		|| (this->itemData->ItemType == "Boots");

	bool isWeapon = (this->itemData->ItemType == "Axe_1H") 
		|| (this->itemData->ItemType == "Axe_2H")
		|| (this->itemData->ItemType == "Mace_1H")
		|| (this->itemData->ItemType == "Mace_2H")
		|| (this->itemData->ItemType == "Sword_1H")
		|| (this->itemData->ItemType == "Sword_2H")
		|| (this->itemData->ItemType == "Sword_2H")
		|| (this->itemData->ItemType == "Crossbow")
		|| (this->itemData->ItemType == "Bow");

	if (isSetItem)
	{
		string defense = "Defense: " + Ogre::StringConverter::toString(this->Defense);
		tooltipItem->mattribute_0_EditBox->setCaption(defense);

		string durability = "Durability [" + StringConverter::toString(this->Durability_Cur) + 
			"/" + StringConverter::toString(this->Durability_Max) + "]";
		tooltipItem->mattribute_1_EditBox->setCaption(durability);

		if (this->Strength_Requeriment > 0)
		{
			string strength_requirement = "Strength Requirement " + StringConverter::toString(this->Strength_Requeriment);
			tooltipItem->mattribute_2_EditBox->setCaption(strength_requirement);
		}
	}

	if (isWeapon)
	{
		string damage = "Damage: " + Ogre::StringConverter::toString(this->Damage_Weapon_Min)
			+ "~" + Ogre::StringConverter::toString(this->Damage_Weapon_Max);
		tooltipItem->mattribute_0_EditBox->setCaption(damage);

		string attack_speed = "Attack Speed [" + StringConverter::toString(this->Speed) + "]";
		tooltipItem->mattribute_1_EditBox->setCaption(attack_speed);

		string durability = "Durability [" + StringConverter::toString(this->Durability_Cur) + 
			"/" + StringConverter::toString(this->Durability_Max) + "]";
		tooltipItem->mattribute_2_EditBox->setCaption(durability);

		if (this->Strength_Requeriment > 0)
		{
			string strength_requirement = "Strength Requirement " + StringConverter::toString(this->Strength_Requeriment);
			tooltipItem->mattribute_3_EditBox->setCaption(strength_requirement);
		}

		if (this->Dexterity_Requeriment > 0)
		{
			string agility_requirement = "Agility Requirement " + StringConverter::toString(this->Dexterity_Requeriment);
			tooltipItem->mattribute_4_EditBox->setCaption(agility_requirement);
		}

		/*string strength_requirement = "Strength Requirement " + StringConverter::toString(this->Strength_Requeriment);
		tooltipItem->mattribute_2_EditBox->setCaption(strength_requirement);*/
	}

	
}

Ogre::Vector3 InventoryItem::getRealInventoryEntityPosition(int x, int y)
{
	Ogre::Vector3 LEFT_UP_PLANE_CORNER = TransformInventoryUtil::getSingletonPtr()->getOriginPositionPlane();
	Ogre::Vector3 final_position = LEFT_UP_PLANE_CORNER + Ogre::Vector3((x + this->offsetPoint.x) / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION
		, -(y + this->offsetPoint.y) / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION , 0);

	return final_position;
}

void InventoryItem::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
	IAttributable::handleAttributeMessage(message);
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
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Defense:
			{
				this->Defense = aatribute->_defaultValue.ValueF;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Durability_Cur:
			{
				this->Durability_Cur = aatribute->_defaultValue.Value;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Durability_Max:
			{
				this->Durability_Max = aatribute->_defaultValue.Value;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Damage_Weapon_Max:
			{
				this->Damage_Weapon_Max = aatribute->_defaultValue.ValueF;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Damage_Weapon_Min:
			{
				this->Damage_Weapon_Min = aatribute->_defaultValue.ValueF;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Speed:
			{
				this->Speed = aatribute->_defaultValue.ValueF;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		case AttributeOpcode::Skill:
			{
				this->Skill = aatribute->_defaultValue.Value;
				/*this->Hitpoints_Cur = aatribute->_defaultValue.ValueF;
				String str = StringConverter::toString(this->Hitpoints_Cur) + "/" + StringConverter::toString(this->Hitpoints_Max);
				GameFramework::getSingletonPtr()->getGameGUI()->getStatsPanel()
					->mhp_EditBox->setCaption(str);*/
				break;
			}
		default:
			{
				LogManager::getSingletonPtr()->logMessage("Could not find attribute " + keyVal->Attribute->Name);
				//OGRE_EXCEPT("Could not find attribute with opcode" + Ogre::StringConverter::toString(keyVal->Index) + "", "");
			}
		}
		this->fillTooltipData();
		LogManager::getSingletonPtr()->logMessage("[Received] " + keyVal->Attribute->Name);
	}
}
}