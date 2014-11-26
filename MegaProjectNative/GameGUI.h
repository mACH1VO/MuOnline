#pragma once
#include "StdAfx.h"

namespace Game
{
	class InventoryItem;
}

class ProfilingPanel;
class MenuPanel;
class DebugPanel;
class LoginPanel;
class InventoryPanel;
class Chat;
class ButtomBar;
class MovePanel;
class StashPanel;
class ShopPanel;
class StatsPanel;
class AuctionHouse;
class TooltipItem;

class GameGUI: public OIS::KeyListener, public OIS::MouseListener
{
public:
	GameGUI(void);
	~GameGUI(void);

	virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
	virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);

	virtual bool mouseMoved(const OIS::MouseEvent &evt);
	virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	
	bool isCursorOnGUI;

	Game::InventoryItem* _temp_itemwidget_for_right_click;


	ProfilingPanel* getProfilingPanel();
	MenuPanel* getMenuPanel();
	DebugPanel* getDebugPanel();
	LoginPanel* getLoginPanel();
	InventoryPanel* getInventoryPanel();
	Chat* getChat();
	ButtomBar* getButtomBar();
	MovePanel* getMovePanel();
	StashPanel* getStashPanel();
	ShopPanel* getShopPanel();
	StatsPanel* getStatsPanel();
	AuctionHouse* getAuctionHouse();
	TooltipItem* getTooltipItem();

	void update(float timeSinceLastFrame);
	void init();

private:
	ProfilingPanel* _profilingPanel;
	MenuPanel* _menuPanel;
	DebugPanel* _debugPanel;
	LoginPanel* _loginPanel;
	InventoryPanel* _inventoryPanel;
	Chat* _chat;
	ButtomBar* _buttomBar;
	MovePanel* _movePanel;
	StashPanel* _stashPanel;
	ShopPanel* _shopPanel;
	StatsPanel* _statsPanel;
	AuctionHouse* _auctionHouse;
	TooltipItem* _tooltipItem;
};
