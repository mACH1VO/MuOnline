#include "StdAfx.h"
#include "LoginPanel.h"
#include "GameClient.h"
#include "GameMessage.h"
#include "GameSetupMessage.h"
#include "GameFramework.h"

LoginPanel::LoginPanel(MyGUI::Widget* _parent)
{
	initialiseByAttributes(this, _parent);
	this->mmu_Ok_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginPanel::mmu_Ok_Button_click);
}

LoginPanel::~LoginPanel()
{
}

void LoginPanel::mmu_Ok_Button_click(MyGUI::WidgetPtr _sender)
{
	std::string acc = this->mmu_Account_EditBox->getOnlyText();
	std::string pw = this->mmu_Password_EditBox->getOnlyText();

	if (!GameFramework::getSingletonPtr()->getGameClient()->isInitialized)
		GameFramework::getSingletonPtr()->getGameClient()->initialize();

	if (GameFramework::getSingletonPtr()->getGameClient()->tryConnect("127.0.0.1", "1999"))
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Connected!");
		Messages::GameSetupMessage gsm;
		gsm.Field0 = 2982.88445;

		GameFramework::getSingletonPtr()->getGameClient()->sendMessage(&gsm);
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("tryconnect error");
	}
	this->mMainWidget->setVisible(false);

	//item_slot_1x1
	//MyGUI::Canvas* item_slot_1x1 = (MyGUI::Canvas*)MyGUI::Gui::getInstance().findWidgetT("item_slot_1x1");
	//item_slot_1x1->setColour(MyGUI::Colour::White);
}