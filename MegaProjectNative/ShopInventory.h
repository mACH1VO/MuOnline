#pragma once
#include "StdAfx.h"
#include "BaseInventory.h"

namespace Messages
{
	class GameMessage;
	class CreateInventoryItemMessage;
}
enum InventoryWindowsID;
namespace Game
{
class Player;
class InventoryItem;
class InventorySlot;
class Equipment;

class ShopInventory : public BaseInventory
{
public:
	ShopInventory(Player* owner);
	~ShopInventory(void);

	void virtual setItemsVisible(bool _visible);

	virtual InventoryWindowsID getInventoryWindowsID();

	virtual InventoryItem* CreateInventoryItem(Messages::CreateInventoryItemMessage* message);
	virtual void ShopInventory::DestroyInventoryItem(InventoryItem* _inventoryItem);

	virtual void update(float timeSinceLastFrame);

};
}
