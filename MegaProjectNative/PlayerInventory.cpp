#include "StdAfx.h"
#include "PlayerInventory.h"
#include "MUEnums.h"
#include "GameMessage.h"
#include "InventoryResponseMoveMessage.h"
#include "InventoryItem.h"
#include "Equipment.h"
#include "Item.h"
#include "CreateInventoryItemMessage.h"
#include "VisualEquipmentMessage.h"
#include "VisualItem.h"
#include "GameFramework.h"
#include "GameGUI.h"
#include "Factory.h"
#include "InventoryPanel.h"
#include "Player.h"
#include "Map.h"

namespace Game
{
PlayerInventory::PlayerInventory(Player* owner)
	:BaseInventory(owner, 7, 12)
{
	//needs this->entity and this->sceneNode initalized
	this->equipment = new Equipment(owner);
}

PlayerInventory::~PlayerInventory(void)
{
}

InventoryWindowsID PlayerInventory::getInventoryWindowsID()
{
	return InventoryWindowsID::_PlayerInventory;
}

InventoryItem* PlayerInventory::CreateInventoryItem(Messages::CreateInventoryItemMessage* message)
{
	return BaseInventory::CreateInventoryItem(message);
}

void PlayerInventory::DestroyInventoryItem(InventoryItem* _inventoryItem)
{
	return BaseInventory::DestroyInventoryItem(_inventoryItem);
}

void PlayerInventory::setItemsVisible(bool _visible)
{
	BaseInventory::setItemsVisible(_visible); 

	//EQUIPMENT!
	std::map<EquipmentSlotId, Game::InventoryItem*>::iterator equip_iter;
	for (equip_iter = this->equipment->itemsEquipedBySlot->begin(); equip_iter != this->equipment->itemsEquipedBySlot->end(); ++equip_iter)
	{
		equip_iter->second->widget->setVisible(_visible);
		equip_iter->second->entity->setVisible(_visible);

		if (_visible)
			equip_iter->second->entity->setRenderQueueGroup(RENDER_QUEUE_INVENTORY_ITEM);
		else
			equip_iter->second->entity->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_MAIN);
	}
}

void PlayerInventory::update(float timeSinceLastFrame)
{
	BaseInventory::update(timeSinceLastFrame);

	//de estos 2, el primero deberia ir a BaseInventory::update no?
	std::map<int, Game::InventoryItem*>::iterator inv_iter;
	for (inv_iter = this->itemsMap->begin(); inv_iter != this->itemsMap->end(); ++inv_iter)
	{
		inv_iter->second->update(timeSinceLastFrame);
	}

	std::map<EquipmentSlotId, Game::InventoryItem*>::iterator equip_iter;
	for (equip_iter = this->equipment->itemsEquipedBySlot->begin(); equip_iter != this->equipment->itemsEquipedBySlot->end(); ++equip_iter)
	{
		equip_iter->second->update(timeSinceLastFrame);
	}
}
void PlayerInventory::Consume(Messages::GameMessage* message) // this is static !
{

}

void PlayerInventory::tryRepositionAllItems()
{
	BaseInventory::tryRepositionAllItems();

	std::map<EquipmentSlotId, Game::InventoryItem*>::iterator equip_iter;
	for (equip_iter = this->equipment->itemsEquipedBySlot->begin(); equip_iter != this->equipment->itemsEquipedBySlot->end(); ++equip_iter)
	{
		int last_x = equip_iter->second->_last_XY_sceneNode_setPosition.x;
		int last_y = equip_iter->second->_last_XY_sceneNode_setPosition.y;

		Vector3 real_position = equip_iter->second->getRealInventoryEntityPosition(last_x, last_y);

		equip_iter->second->sceneNode->setPosition(real_position);
	}
}
}