#pragma once
#include "stdafx.h"
enum InventoryWindowsID;

namespace Messages
{
	class CreateInventoryItemMessage;
}

namespace Game
{
class InventoryItem;
class Actor;
class InventorySlot;
class InventorySize;
class IAttributable;

class BaseInventory
{
public:
	BaseInventory(Game::Actor* _owner, int _rows, int _columns);
	~BaseInventory(void);
	static std::map<int, IAttributable*> globalItemsMap;
	int Rows;
	int Columns;
	std::map<int, Game::InventoryItem*>* itemsMap;
	std::map<std::string, int>* inventoryBackPackMap;
	int** backpack;
	Actor* Owner;

	virtual InventoryWindowsID getInventoryWindowsID();
	void virtual setItemsVisible(bool _visible);

	bool canPutItemThere(InventorySlot _slot, InventorySize _size);
	bool canPutitemThere_checking_self_item(InventorySlot _slot, InventorySize _size, int _dynamicId);
	bool addItemAtPosition(InventoryItem* item, InventorySlot _slot);
	bool removeItem(InventoryItem* item);
	bool hasItem(int _dynamicId);
	int getItemIdBySlot(InventorySlot _slot);

	virtual void tryRepositionAllItems();

	virtual InventoryItem* BaseInventory::CreateInventoryItem(Messages::CreateInventoryItemMessage* message);
	virtual void BaseInventory::DestroyInventoryItem(InventoryItem* _inventoryItem);

	virtual void update(float timeSinceLastFrame);

	/*bool removeItem(InventoryItem* item);
	bool addItemAtPosition(InventoryItem* item, InventorySlot* _slot);*/
};
}
