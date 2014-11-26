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

class StashInventory : public BaseInventory
{
public:
	StashInventory(Player* owner);
	~StashInventory(void);

	void virtual setItemsVisible(bool _visible);

	virtual InventoryWindowsID getInventoryWindowsID();

	virtual InventoryItem* CreateInventoryItem(Messages::CreateInventoryItemMessage* message);
	virtual void StashInventory::DestroyInventoryItem(InventoryItem* _inventoryItem);

	virtual void update(float timeSinceLastFrame);

};
}
