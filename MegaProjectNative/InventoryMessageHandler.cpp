#include "StdAfx.h"
#include "InventoryMessageHandler.h"
#include "GameMessage.h"

#include "MUEnums.h"
#include "InventoryResponseMoveMessage.h"
#include "InventoryItem.h"
#include "Equipment.h"
#include "Item.h"
#include "CreateInventoryItemMessage.h"
#include "InventoryShowWindowMessage.h"
#include "VisualEquipmentMessage.h"
#include "StashPanel.h"
#include "StashInventory.h"
#include "VisualItem.h"
#include "GameFramework.h"
#include "GameGUI.h"
#include "Factory.h"
#include "ShopInventory.h"
#include "ShopPanel.h"
#include "PlayerInventory.h"
#include "InventoryPanel.h"
#include "Player.h"
#include "Map.h"

namespace Game
{
	InventoryMessageHandler::InventoryMessageHandler(void)
	{

	}


	InventoryMessageHandler::~InventoryMessageHandler(void)
	{

	}

	void InventoryMessageHandler::Consume(Messages::GameMessage* message)
	{
	switch(message->opcode)
	{
	case Opcodes::CreateInventoryItemMessage:
		{
			Messages::CreateInventoryItemMessage* msg = (Messages::CreateInventoryItemMessage*)message;
			//Actor* _owner = Map::getSingletonPtr()->actorMap->at(msg->inventoryWindowId);
			if (msg->inventoryWindowId == (int)InventoryWindowsID::_PlayerInventory)
			{
				Player* player = GameFramework::getSingletonPtr()->mainPlayer;
				InventoryItem* invItem = player->inventory->CreateInventoryItem(msg);

				if (!player->inventory->addItemAtPosition(invItem, *msg->inventorySlot))
				{
					Ogre::LogManager::getSingletonPtr()->logMessage("[PlayerInventory] CreateInventoryItem error");
					break;
				}

				//these 2 go afteraddItemAtPosition!
				bool visible = GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel()->getMainWidget()->getVisible();
				player->inventory->setItemsVisible(visible);
			}

			if (msg->inventoryWindowId == (int)InventoryWindowsID::_SHOP)
			{
				Player* player = GameFramework::getSingletonPtr()->mainPlayer;
				if (!player->shopInventory->hasItem(msg->ItemId))
				{
					InventoryItem* invItem = player->shopInventory->CreateInventoryItem(msg);

					if (!player->shopInventory->addItemAtPosition(invItem, *msg->inventorySlot))
					{
						Ogre::LogManager::getSingletonPtr()->logMessage("[PlayershopInventory] CreateInventoryItem error");
						break;
					}

					//these 2 go afteraddItemAtPosition!
					bool visible = GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel()->getMainWidget()->getVisible();
					player->shopInventory->setItemsVisible(visible);
				}
				else
				{
					Ogre::LogManager::getSingletonPtr()->logMessage("[PlayershopInventory] Trying to create an item in shop that already exist!, same itemDynamicId");
				}
			}

			break;
		}
	case Opcodes::DestroyInventoryItemMessage:
		{
			Messages::CreateInventoryItemMessage* msg = (Messages::CreateInventoryItemMessage*)message;
			//Actor* _owner = Map::getSingletonPtr()->actorMap->at(msg->inventoryWindowId);
			if (msg->inventoryWindowId == (int)InventoryWindowsID::_PlayerInventory)
			{
				Player* player = GameFramework::getSingletonPtr()->mainPlayer;
				if (player->inventory->hasItem(msg->ItemId))
				{
					InventoryItem* invItem = ((Player*)player)->inventory->itemsMap->at(msg->ItemId);

					if (invItem->isOnAir)
					{
						invItem->isOnAir = false;
						GameFramework::getSingletonPtr()->itemOnAir = 0;

						MyGUI::PointerManager::getInstancePtr()->setVisible(true);
						//invItem->toolTip->setVisible(true);
					}

					player->inventory->removeItem(invItem); //Logic Part!
					player->inventory->DestroyInventoryItem(invItem);

					/*if (GameFramework::getSingletonPtr()->currentInventoryItemHovered != 0)
					{
						if (GameFramework::getSingletonPtr()->currentInventoryItemHovered->dynamicId == invItem->dynamicId)
							GameFramework::getSingletonPtr()->currentInventoryItemHovered = 0;
					}*/

					/*if (GameFramework::getSingletonPtr()->currentInventoryItemHovered->dynamicId == invItem->dynamicId)
						GameFramework::getSingletonPtr()->currentInventoryItemHovered = 0; //TRICK!*/

				}
				/*else if (((Player*)player)->inventory->equipment->hasItem(msg->ItemId))
				{
					InventoryItem* invItem = ((Player*)_owner)->inventory->equipment->getItemByDynamicId(msg->ItemId);

					if (invItem->isOnAir)
					{
						invItem->isOnAir = false;
						GameFramework::getSingletonPtr()->itemOnAir = 0;
					}

					((Player*)_owner)->inventory->equipment->UnequipItem(invItem); //Logic Part!
					((Player*)_owner)->inventory->DestroyInventoryItem(invItem);
				}
				else
				{
					Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] DestroyInventoryItemMessage error, item to destroy could not be found");
				}*/
			}

			if (msg->inventoryWindowId == (int)InventoryWindowsID::_SHOP)
			{
				Player* player = GameFramework::getSingletonPtr()->mainPlayer;
				if (player->shopInventory->hasItem(msg->ItemId))
				{
					InventoryItem* invItem = ((Player*)player)->shopInventory->itemsMap->at(msg->ItemId);

					player->shopInventory->removeItem(invItem); //Logic Part!
					player->shopInventory->DestroyInventoryItem(invItem);
				}
			}
			break;
		}
	case Opcodes::InventoryResponseMoveMessage:
		{
			Messages::InventoryResponseMoveMessage* msg = (Messages::InventoryResponseMoveMessage*)message;

			InventoryWindowsID origin_window = (InventoryWindowsID)msg->originWindowsID;
			InventoryWindowsID dest_window = (InventoryWindowsID)msg->destinationWindowsID;

			if (GameFramework::getSingletonPtr()->itemOnAir == 0)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] trying to handle InventoryResponseMoveMessage, but itemOnAir = 0");
				break;
			}
			
			if (GameFramework::getSingletonPtr()->itemOnAir->dynamicId != msg->ItemID)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] GameFramework::getSingletonPtr()->itemOnAir->dynamicId != msg->ItemID");
				break;
			}

			Player* player = GameFramework::getSingletonPtr()->mainPlayer;

			//DEST IS PLAYERINVENTORY! (EQUIP OR INV)
			if (dest_window == InventoryWindowsID::_PlayerInventory)
			{
				if (origin_window == InventoryWindowsID::_PlayerInventory)
				{
					//if item destination is inventory! (inventory or equipment!)
					if (player->inventory->hasItem(msg->ItemID))
					{
						if ((EquipmentSlotId)msg->EquipmentSlot != EquipmentSlotId::_Inventory)
						{
							//from inventory to equipment!
							InventoryItem* inv_item = player->inventory->itemsMap->at(msg->ItemID);
							inv_item->acceptItemMovement(msg, InventoryWindowsID::_PlayerInventory);
							player->inventory->removeItem(inv_item);
							player->inventory->equipment->EquipItem(inv_item, (EquipmentSlotId)msg->EquipmentSlot);
						}
						else
						{
							//from inventory to inventory!
							InventoryItem* inv_item = player->inventory->itemsMap->at(msg->ItemID);
							inv_item->acceptItemMovement(msg, InventoryWindowsID::_PlayerInventory);
							player->inventory->removeItem(inv_item);
							player->inventory->addItemAtPosition(inv_item, InventorySlot(msg->Row, msg->Column));
						}
					}
					else
					{
						//from equipment to inventory!
						InventoryItem* inv_item = player->inventory->equipment->getItemByDynamicId(msg->ItemID);
						if (inv_item != 0)
						{
							inv_item->acceptItemMovement(msg, InventoryWindowsID::_PlayerInventory);
							player->inventory->equipment->UnequipItem(inv_item);
							player->inventory->addItemAtPosition(inv_item, InventorySlot(msg->Row, msg->Column));
						}
						else
						{
							Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] error, trying to move an item from equipment to inventory but it is not in equipment!");
						}
					}
				}
				if (origin_window == InventoryWindowsID::Vault)
				{
					if (player->stashInventory->hasItem(msg->ItemID))
					{
						InventoryItem* inv_item = player->stashInventory->itemsMap->at(msg->ItemID);
						inv_item->acceptItemMovement(msg, InventoryWindowsID::_PlayerInventory);
						player->stashInventory->removeItem(inv_item);
						player->inventory->addItemAtPosition(inv_item, InventorySlot(msg->Row, msg->Column));
					}
					else
					{
						Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] error, trying to move an item but item is not in vault!");
					}
				}
			}

			//DEST IS VAULT!
			if (dest_window == InventoryWindowsID::Vault)
			{
				if (origin_window == InventoryWindowsID::Vault)
				{
					//vault to vault!
					if (player->stashInventory->hasItem(msg->ItemID))
					{
						InventoryItem* inv_item = player->stashInventory->itemsMap->at(msg->ItemID);
						inv_item->acceptItemMovement(msg, InventoryWindowsID::Vault);
						player->stashInventory->removeItem(inv_item);
						player->stashInventory->addItemAtPosition(inv_item, InventorySlot(msg->Row, msg->Column));
					}
					else
					{
						Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] error, could not find the item in the vault!");
					}
				}
				if (origin_window == InventoryWindowsID::_PlayerInventory)
				{
					//inventory to vault!
					if (player->inventory->hasItem(msg->ItemID))
					{
						InventoryItem* inv_item = player->inventory->itemsMap->at(msg->ItemID);
						inv_item->acceptItemMovement(msg, InventoryWindowsID::Vault);
						player->inventory->removeItem(inv_item);
						player->stashInventory->addItemAtPosition(inv_item, InventorySlot(msg->Row, msg->Column));
					}
					else
					{
						Ogre::LogManager::getSingletonPtr()->logMessage("[InventoryMessageHandler] error, could not find the item in the inventory!");
					}
				}
			}

			break;
		}
	case Opcodes::VisualEquipmentMessage:
		{
			Messages::VisualEquipmentMessage* msg = (Messages::VisualEquipmentMessage*)message;
			Actor* _owner = Map::getSingletonPtr()->actorMap->at(msg->ActorID);
			if (_owner->getActorType() == ActorType::Player)
			{
				int size_eq = msg->Equipment->size(); //should be 9, testing !
				for (int i = 0; i < msg->Equipment->size()  ; i++)
				{
					EquipmentSlotId slot = (EquipmentSlotId)msg->Equipment->at(i).SlotID;
					int snoId = msg->Equipment->at(i).snoId;

					((Player*)_owner)->inventory->equipment->RefreshVisualItem(slot, snoId);
				}
			}
			else
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("[Error] VisualEquipmentMessage, Actor id is not Player!, id = " + Ogre::StringConverter::toString(msg->ActorID));
			}
			break;
		}

	case Opcodes::InventoryShowWindowMessage:
		{
			Messages::InventoryShowWindowMessage* msg = (Messages::InventoryShowWindowMessage*)message;
			InventoryWindowsID id = (InventoryWindowsID)msg->windowId;

			//trick
			if (MyGUI::PointerManager::getInstancePtr()->getDefaultPointer() == "mu_npc")
				MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("muarrow");

			switch(id)
			{
			case InventoryWindowsID::Vault:
				{
					bool visible = msg->visible;
					GameFramework::getSingletonPtr()->getGameGUI()->getStashPanel()->getMainWidget()->setVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->stashInventory->setItemsVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->hasVaultOpened = visible;
					GameFramework::getSingletonPtr()->mainPlayer->canWalk = !visible;
					break;
				}
			case InventoryWindowsID::_PlayerInventory:
				{
					bool visible = msg->visible;
					GameFramework::getSingletonPtr()->getGameGUI()->getInventoryPanel()->getMainWidget()->setVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->inventory->setItemsVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->hasInventoryOpened = visible;
					break;
				}
			case InventoryWindowsID::_SHOP:
				{
					bool visible = msg->visible;
					GameFramework::getSingletonPtr()->getGameGUI()->getShopPanel()->getMainWidget()->setVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->shopInventory->setItemsVisible(visible);
					GameFramework::getSingletonPtr()->mainPlayer->hasShopOpened = visible;
					GameFramework::getSingletonPtr()->mainPlayer->canWalk = !visible;
					break;
				}
			case InventoryWindowsID::_NPC:
				{
					break;
				}
			default:
				{
					Ogre::LogManager::getSingletonPtr()->logMessage("[Inventory] Consume error in Inventory, InventoryWindowsID not found");
					break;
				}
			}
			break;
		}
	default:
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("[Inventory] Consume error in Inventory, opcode not found ID = " + message->opcode );
			break;
		}
	}
	}
}