#include "stdafx.h"
#include "ButtomBar.h"
#include "TickTimer.h"
#include "GameFramework.h"
#include "MUEnums.h"
#include "Player.h"



ButtomBar::ButtomBar(MyGUI::Widget* _parent)
{
	initialiseByAttributes(this, _parent);
	this->ttupdateGlobe = new TickTimer(40);
	this->currentHPGlobeFrame = 0;
	this->_lastButtonSkillClicked = 0;

	this->mpanel_select_skill_Widget->setVisible(false);

	this->mskill_slot_primaryButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);
	this->mskill_slot_secondaryButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);

	//this->mskill_slot_oneButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);
	//this->mskill_slot_twoButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);
	//this->mskill_slot_threeButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);
	//this->mskill_slot_fourButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_skillButton);

	/*this->mavailable_1_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_2_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_3_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_4_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_5_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_6_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
	this->mavailable_7_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);*/
}

ButtomBar::~ButtomBar()
{

}
void ButtomBar::update(float timeSinceLastFrame)
{
	if (this->ttupdateGlobe->TimedOut())
	{
		this->currentHPGlobeFrame++;
		if (this->currentHPGlobeFrame >= 59)
			this->currentHPGlobeFrame = 0;

		std::string skin_name = "HPResourceGlobe_" + Ogre::StringConverter::toString(this->currentHPGlobeFrame);
		this->mHPResourceGlobeWidget->changeWidgetSkin(skin_name);

		skin_name = "ManaResourceGlobe_" + Ogre::StringConverter::toString(this->currentHPGlobeFrame);
		this->mManaResourceGlobeWidget->changeWidgetSkin(skin_name);

		this->ttupdateGlobe->Reset();
	}

	//int pos = (int)Ogre::Math::RangeRandom(100,150);
	//this->mexperience_bar_ProgressBar->setProgressRange(100);
	//this->mexperience_bar_ProgressBar->setProgressPosition(30);
	
}

void ButtomBar::eventMouseButtonClick_skillButton(MyGUI::WidgetPtr _sender)
{
	this->_lastButtonSkillClicked = _sender;
	this->mpanel_select_skill_Widget->setVisible(!this->mpanel_select_skill_Widget->getVisible());

	//should cast skill here?
}

void ButtomBar::eventMouseButtonClick_availableSkillButton(MyGUI::WidgetPtr _sender)
{
	if (GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->size() <= 0)
		return;

	/*string name = _sender->getName();
	if (MyGUI::Gui::getInstance().findWidgetT(name, false) == nullptr)
		return;*/

	if (this->_lastButtonSkillClicked != 0)
	{
		string name = _sender->getName();
		this->mskill_number_secondary_EditBox->setCaption(""); //clear
		if (name.find("_0_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(0);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}

			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_1_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(1);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_2_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(2);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_3_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(3);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_4_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(4);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_5_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(5);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_6_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(6);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
		if (name.find("_7_") != String::npos)
		{
			SkillOpcode op = GameFramework::getSingletonPtr()->mainPlayer->availableSkillSlots->at(7);
			std::string skin_name = "mu_button_" + skill_opcode_to_string(op);
			this->_lastButtonSkillClicked->changeWidgetSkin(skin_name);
			if (this->_lastButtonSkillClicked->getName().find("primary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Primary] = op;
			}
			if (this->_lastButtonSkillClicked->getName().find("secondary") != String::npos)
			{
				(*GameFramework::getSingleton().mainPlayer->skillSlots)[SkillSlot::Secondary] = op;
			}
			//Ogre::OverlayManager::getSingletonPtr()->
		}
	}
	this->mpanel_select_skill_Widget->setVisible(!this->mpanel_select_skill_Widget->getVisible());
}

void ButtomBar::setVisualSkillIcon(SkillSlot skillSlot, SkillOpcode skillOpcode)
{
	std::string skin_name = "mu_button_" + skill_opcode_to_string(skillOpcode);
	switch(skillSlot)
	{
	case SkillSlot::Primary:
		{
			this->mskill_slot_primaryButton->changeWidgetSkin(skin_name);
			break;
		}
	case SkillSlot::Secondary:
		{
			this->mskill_slot_secondaryButton->changeWidgetSkin(skin_name);
			break;
		}
	/*case SkillSlot::_one:
		{
			this->mskill_slot_oneButton->changeWidgetSkin(skin_name);
			break;
		}
	case SkillSlot::_two:
		{
			this->mskill_slot_twoButton->changeWidgetSkin(skin_name);
			break;
		}
	case SkillSlot::_three:
		{
			this->mskill_slot_threeButton->changeWidgetSkin(skin_name);
			break;
		}
	case SkillSlot::_four:
		{
			this->mskill_slot_fourButton->changeWidgetSkin(skin_name);
			break;
		}
	case SkillSlot::Invalid_slot:
		{
			this->mskill_slot_fourButton->changeWidgetSkin("BackgroundTile");
			break;
		}*/
	}
}

void ButtomBar::setVisualAvailableSkillIcon(int position, SkillOpcode skillOpcode)
{
	std::string skin_name = "mu_button_" + skill_opcode_to_string(skillOpcode);
	std::string button_name = "available_" + Ogre::StringConverter::toString(position) + "_";

	if (MyGUI::Gui::getInstance().findWidgetT(button_name, false) != nullptr)
	{
		LogManager::getSingletonPtr()->logMessage("[WARN] couldn't create available skill icon, button name already exist!, name = " + button_name);
		return;
	}

	int X = 3 + 43 * position;
	int Y = 3;
	int WIDTH = 43;
	int HEIGHT = 43;
	MyGUI::IntCoord coord(X, Y, WIDTH, HEIGHT);

	MyGUI::Button* buttom = this->mpanel_select_skill_Widget->createWidget<MyGUI::Button>(skin_name, coord, MyGUI::Align::Default, button_name);
	buttom->eventMouseButtonClick += MyGUI::newDelegate(this, &ButtomBar::eventMouseButtonClick_availableSkillButton);
}

string ButtomBar::skill_opcode_to_string(SkillOpcode opcode)
{
	switch (opcode)
	{
	case SkillOpcode::Invalid:
		return "Invalid";
	case SkillOpcode::Hand:
		return "Hand";
	case SkillOpcode::Uppercut:
		return "Uppercut";
	case SkillOpcode::Cyclone:
		return "Cyclone";
	case SkillOpcode::Lunge:
		return "Lunge";
	case SkillOpcode::Slash:
		return "Slash";
	case SkillOpcode::Raid:
		return "Raid";
	case SkillOpcode::Impale:
		return "Impale";
	case SkillOpcode::Twisting:
		return "Twisting";
	case SkillOpcode::Inner:
		return "Inner";
	case SkillOpcode::DeathStab:
		return "DeathStab";
	case SkillOpcode::RagefulBlow:
		return "RagefulBlow";
	case SkillOpcode::Strike_of_Destruction:
		return "Strike_of_Destruction";
	case SkillOpcode::Combo:
		return "Combo";
	case SkillOpcode::CrescentMoonSlash:
		return "CrescentMoonSlash";
	case SkillOpcode::BloodStorm:
		return "BloodStorm";
	case SkillOpcode::Defense_:
		return "Defense";
	
	case SkillOpcode::Flame:
		return "Flame";
	case SkillOpcode::Hellfire:
		return "Hellfire";
	case SkillOpcode::AquaBeam:
		return "AquaBeam";
	case SkillOpcode::Cometfall:
		return "Cometfall";
	case SkillOpcode::Inferno:
		return "Inferno";
	
	default:
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("Could not find opcode in skill_opcode_to_string function!");
			return "Invalid";
		}
	}
}

void ButtomBar::setNumberToAvailableSkillButton(int number, SkillOpcode skillOpcode)
{

}
