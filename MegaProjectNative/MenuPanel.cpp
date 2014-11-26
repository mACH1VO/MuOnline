#include "StdAfx.h"
#include "MenuPanel.h"
#include "GameFramework.h"
#include "GameGUI.h"
#include "ProfilingPanel.h"

MenuPanel::MenuPanel(MyGUI::Widget* _parent)
{
	initialiseByAttributes(this, _parent);

	//std::string typenamestr = this->mMainWidget->getClassTypeName();
	//MyGUI::Window* windoww = this->mMainWidget->castType<MyGUI::Window>();

	//this->mMainWidget->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mexit_Button_click);

	this->mexit_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mexit_Button_click);
	this->mselectserver_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mselectserver_Button_click);
	this->mselectcharacter_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mselectcharacter_Button_click);
	this->msettings_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::msettings_Button_click);
	//this->mprofilingtool_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mprofilingtool_Button_click);
	this->mcancel_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &MenuPanel::mcancel_Button_click);

	this->mMainWidget->setVisible(false);

	//this->mMainWidget->setVisible(false);
}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::mexit_Button_click(MyGUI::WidgetPtr _sender)
{
	/*MyGUI::ButtonPtr checkbox = _sender->castType<MyGUI::Button>();
	bool isVisible = GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->getVisible();
	GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->setVisible(true);*/
	//checkbox->setStateCheck(!checkbox->getStateCheck());
}

void MenuPanel::mselectserver_Button_click(MyGUI::WidgetPtr _sender)
{
	//MyGUI::ButtonPtr checkbox = _sender->castType<MyGUI::Button>();
	//bool isVisible = GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->getVisible();
	//GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->setVisible(!isVisible);
	//checkbox->setStateCheck(!checkbox->getStateCheck());
}

void MenuPanel::mselectcharacter_Button_click(MyGUI::WidgetPtr _sender)
{
}

void MenuPanel::msettings_Button_click(MyGUI::WidgetPtr _sender)
{
	//this->mselectcharacter_Button->_setMouseFocus(true);
	//this->mselectcharacter_Button->setpro
}

void MenuPanel::mprofilingtool_Button_click(MyGUI::WidgetPtr _sender)
{
	GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->setVisible(/*!isVisible*/true);
}

void MenuPanel::mcancel_Button_click(MyGUI::WidgetPtr _sender)
{
	this->mMainWidget->setVisible(false);
}