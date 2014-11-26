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

class PlayerInventory : public BaseInventory
{
public:
	PlayerInventory(Player* owner);
	~PlayerInventory(void);

	void virtual setItemsVisible(bool _visible);

	virtual InventoryWindowsID getInventoryWindowsID();

	virtual void tryRepositionAllItems();

	Equipment* equipment;

	virtual InventoryItem* CreateInventoryItem(Messages::CreateInventoryItemMessage* message);
	virtual void PlayerInventory::DestroyInventoryItem(InventoryItem* _inventoryItem);

	virtual void update(float timeSinceLastFrame);

	static void Consume(Messages::GameMessage* message);
};
}
