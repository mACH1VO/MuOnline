#pragma once
#include "stdafx.h"

using namespace Ogre;
namespace Game
{
	class InventorySize;
}
class PlayerData
{
public:
	PlayerData(void);
	~PlayerData(void);

	void PlayerData::Parse(std::string file_name);

	String MeshFileName ;
	String ItemEquipedMeshFileNames ;
	String SkinName ;

	String IdleAnim ;
	String WalkAnim ;
	String AttackAnim ;
	String SkillAnim ;

	float Scale3D ;
	float ScaleTagPoint ;
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
	//ItemQuality Quality ;
	Game::InventorySize* inventorySize ;

};

