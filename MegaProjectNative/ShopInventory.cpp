#include "StdAfx.h"
#include "ShopInventory.h"
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
ShopInventory::ShopInventory(Player* owner)
	:BaseInventory(owner, 16, 10)
{
	//needs this->entity and this->sceneNode initalized
}

ShopInventory::~ShopInventory(void)
{
}

InventoryWindowsID ShopInventory::getInventoryWindowsID()
{
	return InventoryWindowsID::_SHOP;
}

InventoryItem* ShopInventory::CreateInventoryItem(Messages::CreateInventoryItemMessage* message)
{
	InventoryItem* invItem = BaseInventory::CreateInventoryItem(message);
	invItem->isStatic = true;
	return invItem;
}

void ShopInventory::DestroyInventoryItem(InventoryItem* _inventoryItem)
{
	return BaseInventory::DestroyInventoryItem(_inventoryItem);
}

void ShopInventory::setItemsVisible(bool _visible)
{
	BaseInventory::setItemsVisible(_visible); //for grid inventory!
}

void ShopInventory::update(float timeSinceLastFrame)
{
	BaseInventory::update(timeSinceLastFrame);

	//de estos 2, el primero deberia ir a BaseInventory::update no?
	std::map<int, Game::InventoryItem*>::iterator inv_iter;
	for (inv_iter = this->itemsMap->begin(); inv_iter != this->itemsMap->end(); ++inv_iter)
	{
		inv_iter->second->update(timeSinceLastFrame);
	}
}
}