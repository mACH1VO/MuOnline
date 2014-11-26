#include "StdAfx.h"
#include "GameGUI.h"

#include "ProfilingPanel.h"
#include "MenuPanel.h"
#include "DebugPanel.h"
#include "LoginPanel.h"
#include "ShopPanel.h"
#include "InventoryPanel.h"
#include "ButtomBar.h"
#include "Chat.h"
#include "InventoryItem.h"
#include "MovePanel.h"
#include "StashPanel.h"
#include "StatsPanel.h"
#include "AuctionHouse.h"
#include "TooltipItem.h"
#include "Player.h"
#include "PlayerInventory.h"
#include "GameFramework.h"

GameGUI::GameGUI(void)
{
	MyGUI::LayoutManager::getInstance().loadLayout("FPS.layout");
	//MyGUI::LayoutManager::getInstance().loadLayout("Inventory.layout");
	this->isCursorOnGUI = false;
	this->_menuPanel = new MenuPanel();
	this->_profilingPanel = new ProfilingPanel();
	this->_debugPanel = new DebugPanel();
	this->_loginPanel = new LoginPanel();
	this->_inventoryPanel = new InventoryPanel();
	this->_chat = new Chat();
	this->_buttomBar = new ButtomBar();
	this->_movePanel = new MovePanel();
	this->_stashPanel = new StashPanel();
	this->_shopPanel = new ShopPanel();
	this->_statsPanel = new StatsPanel();
	//this->_auctionHouse = new AuctionHouse();
	this->_tooltipItem = new TooltipItem();
	

	this->_inventoryPanel->getMainWidget()->setVisible(false);
	this->_stashPanel->getMainWidget()->setVisible(false);
	this->_shopPanel->getMainWidget()->setVisible(false);
	this->_movePanel->getMainWidget()->setVisible(false);
	this->_statsPanel->getMainWidget()->setVisible(false);
	this->_profilingPanel->getMainWidget()->setVisible(false);
	//this->_auctionHouse->getMainWidget()->setVisible(false);
	this->_tooltipItem->getMainWidget()->setVisible(false);

	this->_chat->getMainWidget()->setVisible(false);

	this->_temp_itemwidget_for_right_click = 0;
}

GameGUI::~GameGUI(void)
{
}

void GameGUI::init()
{
	LogManager::getSingletonPtr()->logMessage(" GameGUI::init() ");
}

bool GameGUI::keyPressed(const OIS::KeyEvent &arg)
{
	switch(arg.key)
	{
	case OIS::KeyCode::KC_1:
		{
			if (this->getChat()->isActive())
				break;

			//get first skill from available skills!
			if (GameFramework::getSingletonPtr()->mainPlayer != 0)
			{
				if (GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->count(0))
				{
					SkillOpcode opcode = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(0);
					this->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, opcode);
					this->getButtomBar()->mskill_number_secondary_EditBox->setCaption("1");
					(*GameFramework::getSingletonPtr()->mainPlayer->skillSlots)[SkillSlot::Secondary] = opcode;
				}
			}
			break;
		}
	case OIS::KeyCode::KC_2:
		{
			if (this->getChat()->isActive())
				break;

			if (GameFramework::getSingletonPtr()->mainPlayer != 0)
			{
				if (GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->count(1))
				{
					SkillOpcode opcode = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(1);
					this->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, opcode);
					this->getButtomBar()->mskill_number_secondary_EditBox->setCaption("2");
					(*GameFramework::getSingletonPtr()->mainPlayer->skillSlots)[SkillSlot::Secondary] = opcode;
				}
			}
			break;
		}
	case OIS::KeyCode::KC_3:
		{
			if (this->getChat()->isActive())
				break;

			if (GameFramework::getSingletonPtr()->mainPlayer != 0)
			{
				if (GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->count(2))
				{
					SkillOpcode opcode = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(2);
					this->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, opcode);
					this->getButtomBar()->mskill_number_secondary_EditBox->setCaption("3");
					(*GameFramework::getSingletonPtr()->mainPlayer->skillSlots)[SkillSlot::Secondary] = opcode;
				}
			}
			break;
		}
	case OIS::KeyCode::KC_4:
		{
			if (this->getChat()->isActive())
			break;

			if (GameFramework::getSingletonPtr()->mainPlayer != 0)
			{
				if (GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->count(3))
				{
					SkillOpcode opcode = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(3);
					this->getButtomBar()->setVisualSkillIcon(SkillSlot::Secondary, opcode);
					this->getButtomBar()->mskill_number_secondary_EditBox->setCaption("4");
					(*GameFramework::getSingletonPtr()->mainPlayer->skillSlots)[SkillSlot::Secondary] = opcode;
				}
			}
			break;
		}
	case OIS::KeyCode::KC_ESCAPE:
		if (this->_menuPanel->getMainWidget()->getVisible() == true)
		{
			this->_menuPanel->getMainWidget()->setVisible(false);
			this->_profilingPanel->getMainWidget()->setVisible(false);
			GameFramework::getSingletonPtr()->cameraMan->mEnabled = true;
		}
		else
		{
			this->_menuPanel->getMainWidget()->setVisible(true);
			GameFramework::getSingletonPtr()->cameraMan->mEnabled = false;
		}
		//this->cameraMan->mGoingForward = true;
		break;
	case OIS::KeyCode::KC_F3:
		{
			if (this->getChat()->isActive())
				break;

			GameFramework::getSingletonPtr()->cameraMan->AutoTrackMainPlayer = !GameFramework::getSingletonPtr()->cameraMan->AutoTrackMainPlayer;
			break;
		}
	case OIS::KeyCode::KC_F2:
		{
			if (this->getChat()->isActive())
				break;

			GameFramework::getSingletonPtr()->cameraMan->mEnabled = !GameFramework::getSingletonPtr()->cameraMan->mEnabled;
			break;
		}
	case OIS::KeyCode::KC_C:
		{
			if (this->getChat()->isActive())
				break;

			this->_statsPanel->getMainWidget()->setVisible(!this->_statsPanel->getMainWidget()->getVisible());
			break;
		}
	case OIS::KeyCode::KC_Z:
		{
			if (this->getChat()->isActive())
				break;

			this->_debugPanel->getMainWidget()->setVisible(!this->_debugPanel->getMainWidget()->getVisible());
			break;
		}
	case OIS::KeyCode::KC_X:
		{
			if (this->getChat()->isActive())
				break;

			//this->_auctionHouse->getMainWidget()->setVisible(!this->_auctionHouse->getMainWidget()->getVisible());
			break;
		}
	case OIS::KeyCode::KC_M:
		{
			if (this->getChat()->isActive())
				break;

			this->_movePanel->getMainWidget()->setVisible(!this->_movePanel->getMainWidget()->getVisible());
			break;
		}
	case OIS::KeyCode::KC_V:
		{
			if (this->getChat()->isActive())
				break;

			this->_inventoryPanel->getMainWidget()->setVisible(!this->_inventoryPanel->getMainWidget()->getVisible());
			
			if (GameFramework::getSingletonPtr()->mainPlayer)
			{
				//si se puso visible el inventorypanel, poner visisble los items!
				GameFramework::getSingletonPtr()->mainPlayer->inventory->setItemsVisible(this->_inventoryPanel->getMainWidget()->getVisible());

				if (GameFramework::getSingletonPtr()->mainPlayer->hasVaultOpened)
				{
					this->_stashPanel->mclose_eventMouseButtonClick(0);
				}

				if (GameFramework::getSingletonPtr()->mainPlayer->hasShopOpened)
				{
					this->_shopPanel->mclose_eventMouseButtonClick(0);
				}
			}
			break;
		}
	case OIS::KeyCode::KC_NUMPADENTER:
	case OIS::KeyCode::KC_RETURN:
		if (this->_chat->getMainWidget()->getVisible())
		{
			this->_chat->ProcessEnter();
			this->_chat->getMainWidget()->setVisible(false);
			this->_chat->getMainWidget()->setEnabled(false);
		}
		else
		{
			this->_chat->getMainWidget()->setVisible(true);
			this->_chat->getMainWidget()->setEnabled(true);
			MyGUI::InputManager::getInstance().setKeyFocusWidget(this->_chat->mnormal_EditBox);
		}
		break;
	}
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameGUI::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameGUI::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameGUI::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (MyGUI::PointerManager::getInstancePtr()->getDefaultPointer() == "muarrow")
		MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("muarrow_click"/*"mu_attack"*//*"mu_npc"*/);
	 


	if (id == OIS::MouseButtonID::MB_Right)
	{
		if (GameFramework::getSingletonPtr()->currentInventoryItemHovered != 0) //si hay algun item abajo del cursor
		{
			this->_temp_itemwidget_for_right_click = GameFramework::getSingletonPtr()->currentInventoryItemHovered;
		}
	}



	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameGUI::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (MyGUI::PointerManager::getInstancePtr()->getDefaultPointer() == "muarrow_click")
		MyGUI::PointerManager::getInstancePtr()->setDefaultPointer("muarrow");

	if (id == OIS::MouseButtonID::MB_Right)
	{
		if (this->_temp_itemwidget_for_right_click != 0)
		{
			//currentInventoryItemHovered
			if ((this->_temp_itemwidget_for_right_click->widget != 0) && (GameFramework::getSingletonPtr()->currentInventoryItemHovered != 0))
			{
				if (this->_temp_itemwidget_for_right_click->widget->getAbsoluteRect().inside(MyGUI::types::TPoint<int>(arg.state.X.abs, arg.state.Y.abs)))
				{
					this->_temp_itemwidget_for_right_click->eventMouseButtonRightClick();
				}
			}
		}
	}

	this->_temp_itemwidget_for_right_click = 0;

	return true;
}

void GameGUI::update(float timeSinceLastFrame)
{
	int x = GameFramework::getSingletonPtr()->lastMouseX;
	int y = GameFramework::getSingletonPtr()->lastMouseY;

	if (MyGUI::LayerManager::getInstancePtr()->getWidgetFromPoint(x,y) != 0)
		this->isCursorOnGUI = true;
	else
		this->isCursorOnGUI = false;

	/*MyGUI::EnumeratorWidgetPtr enumerator = MyGUI::Gui::getInstancePtr()->mWidgetChild();
	int count = enumerator->getChildCount();
	for (int i = 0; i < count; i++)
	{
		MyGUI::Widget* widget_ = enumerator->getChildAt(i);
		std::string name = widget_->getName();
	}*/

	if (this->_profilingPanel != 0)
		this->_profilingPanel->update(timeSinceLastFrame);
	if (this->_buttomBar != 0)
		this->_buttomBar->update(timeSinceLastFrame);
}

ProfilingPanel* GameGUI::getProfilingPanel()
{
	return this->_profilingPanel;
}

MenuPanel* GameGUI::getMenuPanel()
{
	return this->_menuPanel;
}

DebugPanel* GameGUI::getDebugPanel()
{
	return this->_debugPanel;
}

Chat* GameGUI::getChat()
{
	return this->_chat;
}

ButtomBar* GameGUI::getButtomBar()
{
	return this->_buttomBar;
}

InventoryPanel* GameGUI::getInventoryPanel()
{
	return this->_inventoryPanel;
}

MovePanel* GameGUI::getMovePanel()
{
	return this->_movePanel;
}

StashPanel* GameGUI::getStashPanel()
{
	return this->_stashPanel;
}

ShopPanel* GameGUI::getShopPanel()
{
	return this->_shopPanel;
}

StatsPanel* GameGUI::getStatsPanel()
{
	return this->_statsPanel;
}

AuctionHouse* GameGUI::getAuctionHouse()
{
	return this->_auctionHouse;
}

TooltipItem* GameGUI::getTooltipItem()
{
	return this->_tooltipItem;
}