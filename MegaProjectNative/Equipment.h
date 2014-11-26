#pragma once
#include "stdafx.h"

using namespace Ogre;

enum EquipmentSlotId;

namespace Game
{
class Player;
class InventoryItem;

class Equipment
{
public:
	Equipment(Player* owner);
	~Equipment(void);

	Player* Owner;

	Entity* VisualWeapon_R;
	Entity* VisualWeapon_L;

	Entity* VisualHelm;
	Entity* VisualArmor;
	Entity* VisualPants;
	Entity* VisualGloves;
	Entity* VisualBoots;
	Entity* VisualWings;

	std::map<EquipmentSlotId, InventoryItem*>* itemsEquipedBySlot;
	std::map<EquipmentSlotId, int>* visualItemsMap_sno;

	void createBaseSkinEquipment();

	bool Equipment::EquipItem(InventoryItem* _inventoryItem, EquipmentSlotId _slot);
	bool Equipment::UnequipItem(InventoryItem* _inventoryItem);
	bool Equipment::isSlotEmpty(EquipmentSlotId _slot);
	InventoryItem* Equipment::getItemByDynamicId(int _dynamicId);
	bool Equipment::hasItem(int _dynamicId);

	void Equipment::RefreshVisualItem(EquipmentSlotId _slot, int _snoId);

	void Equipment::attachVisualItem(EquipmentSlotId _slot, int _snoId);
	void Equipment::detachCurrentVisualItem(EquipmentSlotId _slot);
};
}