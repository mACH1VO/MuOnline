#include "stdafx.h"
#include "ShopPanel.h"

#include "Item.h"
#include "MUEnums.h"

#include "GameFramework.h"
#include "GameClient.h"

#include "GameMessage.h"
#include "InventoryCloseWindowMessage.h"

	ShopPanel::ShopPanel(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);
		this->mclose_buttonButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ShopPanel::mclose_eventMouseButtonClick);
	}

	ShopPanel::~ShopPanel()
	{
	}

	void ShopPanel::mclose_eventMouseButtonClick(MyGUI::WidgetPtr _sender)
	{
		Messages::InventoryCloseWindowMessage* msg = new Messages::InventoryCloseWindowMessage();
		msg->windowId = InventoryWindowsID::_SHOP;
		GameFramework::getSingletonPtr()->getGameClient()->sendMessage(msg);
		delete msg;
	}


	MyGUI::Widget* ShopPanel::getWidgetSlotByRC(int r, int c)
	{
		std::string str = "shop_slot_";
		str = str + Ogre::StringConverter::toString(r) + "x" + Ogre::StringConverter::toString(c);

		std::string basee = string(this->mMainWidget->getName().begin(), this->mMainWidget->getName().begin() + 9);

		str = basee + str;

		MyGUI::Widget* ret = this->mslot_container_panelWidget->findWidget(str);

		return ret;
	}

	MyGUI::Widget* ShopPanel::getWidgetSlotByScreenPosition(const MyGUI::types::TPoint<int>&  _value)
	{
		int slot_count = this->mslot_container_panelWidget->getChildCount();
		for (int i = 0; i < slot_count; i++)
		{
			MyGUI::Widget* widget = this->mslot_container_panelWidget->getChildAt(i);
			if (widget->getAbsoluteRect().inside(_value))
			{
				MyGUI::types::TRect<int> big_rect = widget->getAbsoluteRect();
				return widget;
			}
		}
		return 0;
	}

	MyGUI::Widget* ShopPanel::getWidgetSlotByScreenPosition_modified(const MyGUI::types::TPoint<int>&  _value)
	{
		int slot_count = this->mslot_container_panelWidget->getChildCount();
		for (int i = 0; i < slot_count; i++)
		{
			MyGUI::Widget* widget = this->mslot_container_panelWidget->getChildAt(i);
			if (widget->getAbsoluteRect().inside(_value))
			{
				MyGUI::types::TRect<int> big_rect = widget->getAbsoluteRect();
				MyGUI::types::TSize<int> big_size = widget->getSize();

				/********/
				/* 1  2 */
				/* 3  4 */
				/********/

				MyGUI::types::TRect<int> rect_1;
				rect_1.set(big_rect.left, big_rect.top, big_rect.left + big_size.width / 2, big_rect.top + big_size.height / 2);

				MyGUI::types::TRect<int> rect_2;
				rect_2.set(big_rect.left + big_size.width / 2, big_rect.top, big_rect.left + big_size.width, big_rect.top + big_size.height / 2);

				MyGUI::types::TRect<int> rect_3;
				rect_3.set(big_rect.left, big_rect.top + big_size.height / 2, big_rect.left + big_size.width / 2, big_rect.top + big_size.height);

				MyGUI::types::TRect<int> rect_4;
				rect_4.set(big_rect.left + big_size.width / 2, big_rect.top + big_size.height / 2, big_rect.left + big_size.width , big_rect.top + big_size.height);

				if (rect_1.inside(_value))
				{
					//LogManager::getSingletonPtr()->logMessage("rect_1");
					return widget;
				}

				if (rect_2.inside(_value))
				{
					//LogManager::getSingletonPtr()->logMessage("rect_2");
					std::string name = widget->getName();
					std::vector<std::string> splitted = MyGUI::utility::split(name, "_");
					if (!splitted.empty())
					{
						std::string slot_num = splitted.at(3);
						std::vector<std::string> splitted_number = MyGUI::utility::split(slot_num, "x");
						if (!splitted_number.empty())
						{
							int r = StringConverter::parseInt(splitted_number.at(0));
							int c = StringConverter::parseInt(splitted_number.at(1));
							MyGUI::Widget* ret = this->getWidgetSlotByRC(r, c+1);
							return ret;
						}
					}
				}

				if (rect_3.inside(_value))
				{
					//LogManager::getSingletonPtr()->logMessage("rect_3");
					std::string name = widget->getName();
					std::vector<std::string> splitted = MyGUI::utility::split(name, "_");
					if (!splitted.empty())
					{
						std::string slot_num = splitted.at(3);
						std::vector<std::string> splitted_number = MyGUI::utility::split(slot_num, "x");
						if (!splitted_number.empty())
						{
							int r = StringConverter::parseInt(splitted_number.at(0));
							int c = StringConverter::parseInt(splitted_number.at(1));
							MyGUI::Widget* ret = this->getWidgetSlotByRC(r+1, c);
							return ret;
						}
					}
				}

				if (rect_4.inside(_value))
				{
					//LogManager::getSingletonPtr()->logMessage("rect_4");
					std::string name = widget->getName();
					std::vector<std::string> splitted = MyGUI::utility::split(name, "_");
					if (!splitted.empty())
					{
						std::string slot_num = splitted.at(3);
						std::vector<std::string> splitted_number = MyGUI::utility::split(slot_num, "x");
						if (!splitted_number.empty())
						{
							int r = StringConverter::parseInt(splitted_number.at(0));
							int c = StringConverter::parseInt(splitted_number.at(1));
							MyGUI::Widget* ret = this->getWidgetSlotByRC(r+1, c+1);
							return ret;
						}
					}
				}

				return widget; //should not return this !
			}
		}
		return 0;
	}

	Game::InventorySlot ShopPanel::getSlotByWidgetName(std::string name)
	{
		Game::InventorySlot return_slot(0,0);
		std::vector<std::string> splitted = MyGUI::utility::split(name, "_");
		if (!splitted.empty())
		{
			std::string slot_num = splitted.at(3);
			std::vector<std::string> splitted_number = MyGUI::utility::split(slot_num, "x");
			if (!splitted_number.empty())
			{
				int r = StringConverter::parseInt(splitted_number.at(0));
				int c = StringConverter::parseInt(splitted_number.at(1));
				return_slot.R = r;
				return_slot.C = c;
				return return_slot;
			}
		}
		return return_slot;
	}

	void ShopPanel::setAllSlotsColor(MyGUI::Colour color)
	{
		int slot_count = this->mslot_container_panelWidget->getChildCount();
		for (int i = 0; i < slot_count; i++)
		{
			MyGUI::Widget* widget = this->mslot_container_panelWidget->getChildAt(i);
			widget->setColour(color);
		}
	}

	void ShopPanel::setHoverSlotsColor(Game::InventorySlot* _slot, Game::InventorySize* _size, MyGUI::Colour color)
	{
		bool set_all_red = false;
		for (int r = _slot->R; r < (_slot->R +_size->Height); r++)
		{
			for (int c = _slot->C; c < (_slot->C + _size->Width); c++)
			{
				Game::InventorySlot temp_slot(r,c);
				MyGUI::Widget* wg = this->getWidgetSlotByRC(r,c);
				if (wg != 0)
					wg->setColour(color);
				else
					set_all_red = true;
			}
		}

		if (set_all_red)
		{
			for (int r = _slot->R; r < (_slot->R +_size->Height); r++)
			{
				for (int c = _slot->C; c < (_slot->C + _size->Width); c++)
				{
					MyGUI::Widget* wg = this->getWidgetSlotByRC(r,c);
					if (wg != 0)
						wg->setColour(MyGUI::Colour::Red);
				}
			}
		}
	}

	void ShopPanel::setHoverSlotsColor(const MyGUI::types::TRect<int>&  _value , MyGUI::Colour color)
	{
		int slot_count = this->mslot_container_panelWidget->getChildCount();
		for (int i = 0; i < slot_count; i++)
		{
			MyGUI::Widget* widget = this->mslot_container_panelWidget->getChildAt(i);
			MyGUI::IntRect rectangle = widget->getAbsoluteRect();
			MyGUI::IntSize _size = widget->getSize();
			MyGUI::IntPoint center_rectangle = MyGUI::IntPoint(rectangle.left + (_size.width / 2), rectangle.top + (_size.height / 2));
			//((center_rectangle.left > _value.left) && (center_rectangle.left < _value.right) && (center_rectangle.top > _value.top) && (center_rectangle.top < _value.bottom));
			if (((center_rectangle.left >= _value.left) && (center_rectangle.left < _value.right) && (center_rectangle.top >= _value.top) && (center_rectangle.top < _value.bottom)))
			{
				//en el check de arriba, algunos son con igual y otros no porque sino se seleccionan mal, o 2 de 4 o 6 de 4 !
				widget->setColour(color);
			}
		}
	}
