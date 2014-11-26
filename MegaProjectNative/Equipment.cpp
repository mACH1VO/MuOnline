#include "StdAfx.h"
#include "Equipment.h"
#include "GameFramework.h"
#include "InventoryItem.h"
#include "MUEnums.h"
#include "Player.h"
#include "Storage.h"
#include "ItemData.h"
#include "OgreTagPoint.h"

using namespace Ogre;

namespace Game
{
Equipment::Equipment(Player* owner)
{
	this->Owner = owner;
	this->VisualBoots = 0;
	this->VisualGloves = 0;
	this->VisualHelm = 0;
	this->VisualWeapon_L = 0;
	this->VisualWeapon_R = 0;
	this->VisualPants = 0;
	this->VisualWings = 0;

	itemsEquipedBySlot = new std::map<EquipmentSlotId, InventoryItem*>();
	visualItemsMap_sno = new std::map<EquipmentSlotId, int>();
}

Equipment::~Equipment(void)
{
}

void Equipment::createBaseSkinEquipment()
{
	Entity* ent;

	ent = GameFramework::getSingletonPtr()->sceneManager->createEntity("ArmorClass202.mesh");
	this->Owner->sceneNode->attachObject(ent);
	ent->shareSkeletonInstanceWith(this->Owner->entity);
	this->VisualArmor = ent;
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Armor, 0));


	ent = GameFramework::getSingletonPtr()->sceneManager->createEntity("HelmClass202.mesh");
	this->Owner->sceneNode->attachObject(ent);
	ent->shareSkeletonInstanceWith(this->Owner->entity);
	this->VisualHelm = ent;
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Helm, 0));


	ent = GameFramework::getSingletonPtr()->sceneManager->createEntity("GloveClass202.mesh");
	this->Owner->sceneNode->attachObject(ent);
	ent->shareSkeletonInstanceWith(this->Owner->entity);
	this->VisualGloves = ent;
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Gloves, 0));


	ent = GameFramework::getSingletonPtr()->sceneManager->createEntity("PantClass202.mesh");
	this->Owner->sceneNode->attachObject(ent);
	ent->shareSkeletonInstanceWith(this->Owner->entity);
	this->VisualPants = ent;
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Pants, 0));


	ent = GameFramework::getSingletonPtr()->sceneManager->createEntity("BootClass202.mesh");
	this->Owner->sceneNode->attachObject(ent);
	ent->shareSkeletonInstanceWith(this->Owner->entity);
	this->VisualBoots = ent;
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Boots, 0));



	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Fairy, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Wing, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Necklace, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Ring_left, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Ring_right, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Weapon_L, 0));
	this->visualItemsMap_sno->insert(std::make_pair(EquipmentSlotId::Weapon_R, 0));
}

bool Equipment::EquipItem(InventoryItem* _inventoryItem, EquipmentSlotId _slot)
{
	if (!this->itemsEquipedBySlot->count(_slot))
	{
		this->itemsEquipedBySlot->insert(std::make_pair(_slot, _inventoryItem));
		_inventoryItem->equipmentSlot = _slot;
		return true;
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage(LogMessageLevel::LML_CRITICAL, "[Equipment] trying to equip item but slot is ocupied!");
		return false;
	}
}

bool Equipment::UnequipItem(InventoryItem* _inventoryItem)
{
	EquipmentSlotId _slot = _inventoryItem->equipmentSlot;

	if (this->itemsEquipedBySlot->count(_slot))
	{
		this->itemsEquipedBySlot->erase(_slot);
		_inventoryItem->equipmentSlot = EquipmentSlotId::_Inventory; //hmmmm
		return true;
	}
	else
	{
		LogManager::getSingletonPtr()->logMessage(LogMessageLevel::LML_CRITICAL, "[Equipment] trying to unequip item that doesn't exist!");
		return false;
	}
}

bool Equipment::isSlotEmpty(EquipmentSlotId _slot)
{
	if (this->itemsEquipedBySlot->count(_slot))
	{
		return false;
	}
	else
	{
		return true;
	}
}

InventoryItem* Equipment::getItemByDynamicId(int _dynamicId)
{
	std::map<EquipmentSlotId, Game::InventoryItem*>::iterator equip_iter;
	for (equip_iter = this->itemsEquipedBySlot->begin(); equip_iter != this->itemsEquipedBySlot->end(); ++equip_iter)
	{
		if (equip_iter->second->dynamicId == _dynamicId)
			return equip_iter->second;
	}

	return 0;
}

bool Equipment::hasItem(int _dynamicId)
{
	std::map<EquipmentSlotId, Game::InventoryItem*>::iterator equip_iter;
	for (equip_iter = this->itemsEquipedBySlot->begin(); equip_iter != this->itemsEquipedBySlot->end(); ++equip_iter)
	{
		if (equip_iter->second->dynamicId == _dynamicId)
			return true;
	}

	return false;
}

void Equipment::RefreshVisualItem(EquipmentSlotId _slot, int _snoId)
{
	 /*
	 std::string fileName = Storage::getSingletonPtr()->snoMap->at(_snoId);
	 ItemData* itemData = new ItemData();
	 itemData->Parse(fileName + ".xml");
	 */

	if (this->visualItemsMap_sno->at(_slot) != _snoId)
	{
		this->detachCurrentVisualItem(_slot);
		this->attachVisualItem(_slot, _snoId); //0 = piel
	}
}

void Equipment::attachVisualItem(EquipmentSlotId _slot, int _snoId)
{
	if (this->visualItemsMap_sno->at(_slot) == _snoId)
		return;

	(*this->visualItemsMap_sno)[_slot] = _snoId;

	if (this->Owner->isMoving)
		this->Owner->StopMoving();

	std::string meshName;

	if (_snoId != 0)
	{
		std::string fileName = Storage::getSingletonPtr()->snoMap->at(_snoId);
		ItemData itemData;
		itemData.Parse(fileName + ".xml");

		meshName = itemData.ItemEquipedMeshFileNames;
	}
	else
	{
		if (_slot == EquipmentSlotId::Armor)
			meshName = "ArmorClass202.mesh";
		if (_slot == EquipmentSlotId::Helm)
			meshName = "HelmClass202.mesh";
		if (_slot == EquipmentSlotId::Pants)
			meshName = "PantClass202.mesh";
		if (_slot == EquipmentSlotId::Boots)
			meshName = "BootClass202.mesh";
		if (_slot == EquipmentSlotId::Gloves)
			meshName = "GloveClass202.mesh";
		if (_slot == EquipmentSlotId::Weapon_L)
			meshName = "";
		if (_slot == EquipmentSlotId::Wing)
			meshName = "";
	}

	switch (_slot)
	{
	case EquipmentSlotId::Helm:
		{
			Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
			this->Owner->sceneNode->attachObject(ent);
            ent->shareSkeletonInstanceWith(this->Owner->entity);
            this->VisualHelm = ent;
            break;
		}
	case EquipmentSlotId::Armor:
		{
			Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
			this->Owner->sceneNode->attachObject(ent);
			ent->shareSkeletonInstanceWith(this->Owner->entity);
			this->VisualArmor = ent;
			break;
		}
	case EquipmentSlotId::Gloves:
		{
			Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
			this->Owner->sceneNode->attachObject(ent);
			ent->shareSkeletonInstanceWith(this->Owner->entity);
			this->VisualGloves = ent;
			break;
		}
	case EquipmentSlotId::Pants:
		{
			Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
			this->Owner->sceneNode->attachObject(ent);
			ent->shareSkeletonInstanceWith(this->Owner->entity);
			this->VisualPants = ent;
			break;
		}
	case EquipmentSlotId::Boots:
		{
			Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
			this->Owner->sceneNode->attachObject(ent);
			ent->shareSkeletonInstanceWith(this->Owner->entity);
			this->VisualBoots = ent;
			break;
		}
	case EquipmentSlotId::Weapon_L:
		{
			if (meshName != "")
			{
				Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
				Quaternion initOr = Quaternion::IDENTITY;
				initOr.FromAngleAxis(Degree(90), Vector3::UNIT_X);
				bool is_ent_visible = this->VisualGloves->isVisible();
				bool is_ent_visible2 = this->Owner->entity->isVisible();
				TagPoint* tp = this->Owner->entity->attachObjectToBone("knife_gdf", ent, initOr);
				/*Vector3 TP_SCALE = Vector3::UNIT_SCALE;
				tp->scale(TP_SCALE);*/
				this->VisualWeapon_L = ent;
			}
			this->Owner->PlayAnimation("Idle", true, BlendingTransition::BlendSwitch);
			/*this.Owner.PlayAnimation("Idle", true); //refresh anim, asi mueve acomoda los brazos para la weapon
			this.VisualMainHand.Add(ent);*/
			break;
		}
	case EquipmentSlotId::Wing:
		{
			if (meshName != "")
			{
				Entity* ent = GameFramework::getSingletonPtr()->sceneManager->createEntity(meshName);
				ent->getSkeleton()->getAnimation("Play")->setInterpolationMode(Animation::InterpolationMode::IM_LINEAR);
				//ent->getSkeleton()->getAnimation("Play")->setRotationInterpolationMode(Animation::RotationInterpolationMode::RIM_LINEAR);
				ent->setCastShadows(false);
				//ent->setRenderQueueGroup(49);
				//TagPoint tp1 = GameGlobal.MainPlayer.Equipment.VisualArmor_SKIN_BASE.FirstOrDefault().AttachObjectToBone("mmm", ent);
				TagPoint* tp1 = this->Owner->entity->attachObjectToBone("mmm", ent);
				tp1->setInheritParentEntityScale(true);
				this->VisualWings = ent;

				this->Owner->hasWings = true;
				this->Owner->PlayAnimation("Idle", true); //refresh anim
			}
			break;
		}
	default:
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(LogMessageLevel::LML_CRITICAL, "[Equipment] detachCurrentVisualItem slot id not recognized");
		}
	}
}

void Equipment::detachCurrentVisualItem(EquipmentSlotId _slot)
{
	/*if (this->visualItemsEquipedBySlot_sno->at(_slot) == 0)
		return;*/

	switch (_slot)
	{
	case EquipmentSlotId::Helm:
		{
			this->VisualHelm->stopSharingSkeletonInstance();
			this->Owner->sceneNode->detachObject(this->VisualHelm);
			GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualHelm);
			break;
		}
	case EquipmentSlotId::Armor:
		{
			this->VisualArmor->stopSharingSkeletonInstance();
			this->Owner->sceneNode->detachObject(this->VisualArmor);
			GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualArmor);
			break;
		}
	case EquipmentSlotId::Gloves:
		{
			this->VisualGloves->stopSharingSkeletonInstance();
			this->Owner->sceneNode->detachObject(this->VisualGloves);
			this->VisualGloves->detachFromParent();
			GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualGloves);
			break;
		}
	case EquipmentSlotId::Boots:
		{
			this->VisualBoots->stopSharingSkeletonInstance();
			this->Owner->sceneNode->detachObject(this->VisualBoots);
			GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualBoots);
			break;
		}
	case EquipmentSlotId::Pants:
		{
			this->VisualPants->stopSharingSkeletonInstance();
			this->Owner->sceneNode->detachObject(this->VisualPants);
			GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualPants);
			break;
		}
	case EquipmentSlotId::Weapon_L:
		{
			if (this->VisualWeapon_L != 0)
			{
				//should delete the tagpoint?
				this->VisualWeapon_L->detachFromParent();
				GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualWeapon_L);
				this->VisualWeapon_L = 0;
				//this.Owner.PlayAnimation("Idle", true); //refresh anim, asi mueve acomoda los brazos
				//this.VisualMainHand.Clear();
			}
		break;
		}
	case EquipmentSlotId::Wing:
		{
			if (this->VisualWings != 0)
			{
				this->VisualWings->detachFromParent();
				GameFramework::getSingletonPtr()->sceneManager->destroyEntity(this->VisualWings);
				this->VisualWings = 0; //este antes de play animation!
				this->Owner->hasWings = false;
				this->Owner->PlayAnimation("Idle", true); //refresh anim
				
			}
			break;
		}
	default:
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(LogMessageLevel::LML_CRITICAL, "[Equipment] detachCurrentVisualItem slot id not recognized");
		}
	}
}
}