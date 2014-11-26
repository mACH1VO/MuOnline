#pragma once
#include "StdAfx.h"
#include "IAttributable.h"

class ItemData;
enum EquipmentSlotId;
enum InventoryWindowsID;
enum RotationAxis;

namespace Messages
{
	class InventoryResponseMoveMessage;
	class GameMessage;
	class AttributesSetValuesMessage;
}

namespace Game
{
class InventorySize;
class InventorySlot;
class BaseInventory;

class InventoryItem : public IAttributable
{
public:
	InventoryItem(int _dynamicId, int _sno, InventorySlot* _invSlot, BaseInventory* _inventory);
	~InventoryItem(void);

	int dynamicId;
	bool isOnAir;
	bool isMouseHover;
	bool isStatic;
	ItemData* itemData;

	BaseInventory* baseInventory;

	EquipmentSlotId equipmentSlot;

	InventorySize* inventorySize;
	InventorySlot* inventorySlot;

	MyGUI::Widget* widget;

	Ogre::Entity* entity;
	Ogre::SceneNode* sceneNode;

	Ogre::Vector2 offsetPoint;

	Ogre::Vector2 _last_XY_sceneNode_setPosition;

	void acceptItemMovement(Messages::InventoryResponseMoveMessage* msg, InventoryWindowsID dest_window_id);
	void setToolTipRightPosition();
	void fillTooltipData();
	void createWidgetandSetUpCallbacks();

	Ogre::Vector3 getRealInventoryEntityPosition(int x, int y);
	void update(float timeSinceLastFrame);

	void eventChangeCoord(MyGUI::WidgetPtr _sender);
	void eventMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old);
	void eventMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old);
	void eventMouseButtonClick(MyGUI::WidgetPtr _sender);
	void eventMouseButtonRightClick();

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

	int Level;
	int Defense;
	int DefenseRate;
	int Durability_Cur;
	int Durability_Max;
	int Strength_Requeriment;
	int Dexterity_Requeriment;
	int Vitality_Requeriment;
	int Intelligence_Requeriment;
	int Level_Requeriment;

	int Damage_Weapon_Max;
	int	Damage_Weapon_Min;
	int Speed;
	int Skill;

private:
	bool _waiting_for_request_response;
	Ogre::Quaternion _initial_orientation;
	RotationAxis rotationAxis; 
};
}
