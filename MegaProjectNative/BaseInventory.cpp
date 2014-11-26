#include "StdAfx.h"
#include "BaseInventory.h"
#include "InventoryItem.h"
#include "MUEnums.h"
#include "Item.h"

#include "IAttributable.h"

#include "GameMessage.h"
#include "CreateInventoryItemMessage.h"
#include "DestroyInventoryItemMessage.h"

namespace Game
{

std::map<int, IAttributable*> BaseInventory::globalItemsMap;

BaseInventory::BaseInventory(Actor* _owner, int _rows, int _columns)
{
	this->Rows = _rows;
	this->Columns = _columns;
	this->Owner = _owner;

	this->itemsMap = new std::map<int, InventoryItem*>();
	this->inventoryBackPackMap = new std::map<std::string, int>();

	for (int r = 0; r < this->Rows; r++)
	{
		for (int c = 0; c < this->Columns; c++)
		{
			InventorySlot temp_slot(r,c);

			std::string key = temp_slot.toString();

			this->inventoryBackPackMap->insert(std::make_pair(key, 0));
		}
	}
	/*this->backpack = new int*[_rows];
	for(int i = 0; i < _rows; i++)
	{
		this->backpack[i] = new int[_columns];
	}*/
}

BaseInventory::~BaseInventory(void)
{
	/*for(int i = 0; i < this->Rows; i++)
	{
		delete [] this->backpack[i];
	}
	delete [] this->backpack;*/
}

InventoryWindowsID BaseInventory::getInventoryWindowsID()
{
	return InventoryWindowsID::_PlayerInventory;
}

void BaseInventory::update(float timeSinceLastFrame)
{
}

bool BaseInventory::canPutItemThere(InventorySlot _slot, InventorySize _size)
{
	if (this->inventoryBackPackMap->count(_slot.toString()))
	{
		for (int r = _slot.R; r < (_slot.R +_size.Height); r++)
		{
			for (int c = _slot.C; c < (_slot.C + _size.Width); c++)
			{
				InventorySlot temp_slot(r,c);

				std::string key = temp_slot.toString();

				int dynamic_id = this->inventoryBackPackMap->at(key);

				if (dynamic_id != 0)
					return false;
			}
		}
	}
	return true;
}

bool BaseInventory::canPutitemThere_checking_self_item(InventorySlot _slot, InventorySize _size, int _dynamicId)
{
	if (this->inventoryBackPackMap->count(_slot.toString()))
	{
		for (int r = _slot.R; r < (_slot.R +_size.Height); r++)
		{
			for (int c = _slot.C; c < (_slot.C + _size.Width); c++)
			{
				InventorySlot temp_slot(r,c);

				std::string key = temp_slot.toString();

				int dynamic_id = this->inventoryBackPackMap->at(key);

				if ((dynamic_id != 0) && (dynamic_id != _dynamicId))
					return false;
			}
		}
	}
	return true;
}

int BaseInventory::getItemIdBySlot(InventorySlot _slot)
{
	std::string key = _slot.toString();

	int dynamic_id = this->inventoryBackPackMap->at(key);

	return dynamic_id;
}
void BaseInventory::setItemsVisible(bool _visible)
{
	std::map<int, Game::InventoryItem*>::iterator inv_iter;
	for (inv_iter = this->itemsMap->begin(); inv_iter != this->itemsMap->end(); ++inv_iter)
	{
		inv_iter->second->widget->setVisible(_visible);
		inv_iter->second->entity->setVisible(_visible);
		inv_iter->second->entity->getParentSceneNode()->setVisible(_visible);

		if (_visible)
			inv_iter->second->entity->setRenderQueueGroup(RENDER_QUEUE_INVENTORY_ITEM);
		else
			inv_iter->second->entity->setRenderQueueGroup(RenderQueueGroupID::RENDER_QUEUE_MAIN);
	}
}

bool BaseInventory::hasItem(int _dynamicId)
{
	if (this->itemsMap->count(_dynamicId))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BaseInventory::removeItem(InventoryItem* item)
{
	if (this->itemsMap->count( item->dynamicId ))
	{
		this->itemsMap->erase(item->dynamicId);

		InventorySlot* _slot = item->inventorySlot;
		InventorySize* _size = item->inventorySize;
		for (int r = _slot->R; r < (_slot->R +_size->Height); r++)
		{
			for (int c = _slot->C; c < (_slot->C + _size->Width); c++)
			{
				InventorySlot temp_slot(r,c);
				std::string key = temp_slot.toString();

				(*this->inventoryBackPackMap)[key] = 0; //this->inventoryBackPackMap->insert(std::make_pair(key, 0));
			}
		}

		item->inventorySlot->R = 0;
		item->inventorySlot->C = 0;

		return true;
	}
	else
	{
		return false;
	}
}

void BaseInventory::tryRepositionAllItems()
{
	std::map<int, Game::InventoryItem*>::iterator inv_iter;
	for (inv_iter = this->itemsMap->begin(); inv_iter != this->itemsMap->end(); ++inv_iter)
	{
		int last_x = inv_iter->second->_last_XY_sceneNode_setPosition.x;
		int last_y = inv_iter->second->_last_XY_sceneNode_setPosition.y;

		Vector3 real_position = inv_iter->second->getRealInventoryEntityPosition(last_x, last_y);
		
		inv_iter->second->sceneNode->setPosition(real_position);
	}
}

bool BaseInventory::addItemAtPosition(InventoryItem* item, InventorySlot _slot)
{
	InventorySize _size;
	_size.Width = item->inventorySize->Width;
	_size.Height = item->inventorySize->Height;

	//check backpack boundaries
	if (_slot.R + _size.Height > this->Rows || _slot.C + _size.Width > this->Columns)
		return false;

	//if (!this->itemsMap->count( item->dynamicId ))
	this->itemsMap->insert(std::make_pair(item->dynamicId, item));

	for (int r = _slot.R; r < (_slot.R +_size.Height); r++)
	{
		for (int c = _slot.C; c < (_slot.C + _size.Width); c++)
		{
			InventorySlot temp_slot(r,c);
			std::string key = temp_slot.toString();
			int value = item->dynamicId;

			(*this->inventoryBackPackMap)[key] = value; //->insert(std::map<string, int>::value_type(key, value));
		}
	}

	item->inventorySlot->R = _slot.R;
	item->inventorySlot->C = _slot.C;

	return true;
}

InventoryItem* BaseInventory::CreateInventoryItem(Messages::CreateInventoryItemMessage* message)
{
	InventoryItem* invItem = new InventoryItem(message->ItemId, message->SNO, message->inventorySlot, this);
	invItem->createWidgetandSetUpCallbacks();

	BaseInventory::globalItemsMap[invItem->dynamicId] = invItem;

	return invItem;
}

void BaseInventory::DestroyInventoryItem(InventoryItem* _inventoryItem)
{
	BaseInventory::globalItemsMap.erase(_inventoryItem->dynamicId);
	delete _inventoryItem;
}
}