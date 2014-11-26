#include "stdafx.h"
#include "StatsPanel.h"
#include "GameMessage.h"
#include "AssignStatMessage.h"
#include "MUEnums.h"

#include "GameFramework.h"
#include "Player.h"
#include "GameClient.h"

	StatsPanel::StatsPanel(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);

		this->mstrength_button_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &StatsPanel::eventMouseButtonClick_statButton);
		this->magility_button_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &StatsPanel::eventMouseButtonClick_statButton);
		this->mstamina_button_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &StatsPanel::eventMouseButtonClick_statButton);
		this->menergy_button_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &StatsPanel::eventMouseButtonClick_statButton);
	}

	StatsPanel::~StatsPanel()
	{
	}

	void StatsPanel::eventMouseButtonClick_statButton(MyGUI::WidgetPtr _sender)
	{
		Messages::AssignStatMessage* msg = new Messages::AssignStatMessage();
		string name  = _sender->getName();
		if (name.find("strength")!= string::npos)
		{
			msg->StatType = StatType::Strength_;
		}
		else if (name.find("agility")!= string::npos)
		{
			msg->StatType = StatType::Agility_;
		}
		else if (name.find("stamina")!= string::npos)
		{
			msg->StatType = StatType::Stamina_;
		}
		else if (name.find("energy")!= string::npos)
		{
			msg->StatType = StatType::Energy_;
		}
		else
		{
			msg->StatType = StatType::Strength_; //DEFAULT!
		}
		if (GameFramework::getSingletonPtr()->mainPlayer)
		{
			GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
		}

		delete msg;
	}