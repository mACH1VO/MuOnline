#pragma once
#include "stdafx.h"

using namespace Ogre;
namespace Game
{
	class InventorySize;
}
class ItemData
{
public:
	ItemData(void);
	~ItemData(void);

	void ItemData::Parse(std::string file_name);

	String MeshFileName ;
	String ItemEquipedMeshFileNames ;
	String SkinName ;

	String IdleAnim ;
	String WalkAnim ;
	String AttackAnim ;
	String SkillAnim ;

	float Scale3D ;
	float ScaleTagPoint ;
	float BaseScale3D;
	float HoverScale3D;
	Ogre::Vector2 OffsetPoint;
	int Hash ;
	String Name ;
	int SNOActor ;
	String ItemType ;
	int ItemLevel ;
	int BaseGoldValue ;
	int RequiredLevel ;
	int DurabilityMin ;
	int DurabilityDelta ;
	float WeaponDamageMin ;
	float WeaponDamageDelta ;
	float ArmorValue ;
	float AttacksPerSecond ;
	String HideMaterialName;
	//ItemQuality Quality ;
	Game::InventorySize* inventorySize ;

};

