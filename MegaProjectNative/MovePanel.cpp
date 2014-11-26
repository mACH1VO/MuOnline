#include "stdafx.h"
#include "MovePanel.h"

	MovePanel::MovePanel(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);

		this->mbutton_list_1Button->eventMouseSetFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseSetFocus);
		this->mbutton_list_1Button->eventMouseLostFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseLostFocus);

		this->mbutton_list_2Button->eventMouseSetFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseSetFocus);
		this->mbutton_list_2Button->eventMouseLostFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseLostFocus);

		this->mbutton_list_3Button->eventMouseSetFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseSetFocus);
		this->mbutton_list_3Button->eventMouseLostFocus += MyGUI::newDelegate(this, &MovePanel::eventMouseLostFocus);
	}

	MovePanel::~MovePanel()
	{
	}

	void MovePanel::eventMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old)
	{
		_sender->changeWidgetSkin("mu_movepanel_hoverbutton");
	}

	void MovePanel::eventMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old)
	{
		_sender->changeWidgetSkin("ButtonEmptySkin");
	}