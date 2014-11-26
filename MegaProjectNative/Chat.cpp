#include "stdafx.h"
#include "GameClient.h"
#include "GameFramework.h"
#include "GameMessage.h"
#include "ChatMessage.h"
#include "Chat.h"
#include "MUEnums.h"
#include "Map.h"
#include "Actor.h"
#include "Player.h"

	Chat::Chat(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);
		this->recorded_deque_text = new std::deque<string>();

		this->mnormal_EditBox->eventKeyButtonPressed += MyGUI::newDelegate(this, &Chat::mnormal_EditBox_eventKeyButtonPressed);
		this->_indexEditBoxArrows = 0;
		//this->mnormal_EditBox->setNeedKeyFocus(true);
		//this->mnormal_EditBox->setNeedMouseFocus(true);
	}

	Chat::~Chat()
	{
	}

	void Chat::Consume(Messages::GameMessage* message)
	{
		switch(message->opcode)
		{
		case Opcodes::ChatMessage:
			{
				
				Messages::ChatMessage* msg = (Messages::ChatMessage*)message;

				//show chat widget over actor (always player?)
				if (Game::Map::getSingletonPtr()->actorMap->count(msg->ActorDynamicID))
				{
					Game::Actor* actor = Game::Map::getSingletonPtr()->actorMap->at(msg->ActorDynamicID);
					if (actor->getActorType() == ActorType::Player)
					{
						std::string playerName = ((Game::Player*)actor)->name;
						((Game::Player*)actor)->say(/*playerName + ": " +*/ msg->Text, 5000); //5 seg
					}
					else
					{
						LogManager::getSingletonPtr()->logMessage("[Chat] Consume, trying to say something but actor is not Player!");
					}
				}

				std::string text = msg->Text;

				if (text != "")
				{
					string color_red = "#dddddd";
					this->recorded_deque_text->push_back("#8490ffelgordito: " + color_red + text);
					if (this->recorded_deque_text->size() > 50)
					{
						this->recorded_deque_text->pop_front();
					}
				}

				//this->mchat_record_EditBox->addText(text);

				this->mchat_record_EditBox->setCaption("");

				std::deque<string>::iterator it;
				for (it = this->recorded_deque_text->begin(); it != this->recorded_deque_text->end(); ++it)
				{
					string str = *it;
					str = str + "\n";
					this->mchat_record_EditBox->addText(str);
				}

				//this->mnormal_EditBox->setCaption("");
				break;

			}
		default:
			{
				LogManager::getSingletonPtr()->logMessage("Chat::Consume id not recognized");
				break;
			}
		}
	}

	void Chat::ProcessEnter()
	{
		string text = this->mnormal_EditBox->getOnlyText();
		
		this->_indexEditBoxArrows = 0;

		/*if (text != "")
		{
			this->recorded_deque_text->push_back(text);
			if (this->recorded_deque_text->size() > 50)
			{
				this->recorded_deque_text->pop_front();
			}
		}
		this->mchat_record_EditBox->setCaption("");

		std::deque<string>::iterator it;
		for (it = this->recorded_deque_text->begin(); it != this->recorded_deque_text->end(); ++it)
		{
			string str = *it;
			str = str + "\n";
			this->mchat_record_EditBox->addText(str);
		}*/

		this->mnormal_EditBox->setCaption("");

		if (text != "")
		{
			Messages::ChatMessage* cm = new Messages::ChatMessage();
			cm->ActorDynamicID = 0;
			cm->Lengh = text.length();
			cm->Text = text;
			cm->Type = 1;
			Networking::GameClient* gc = GameFramework::getSingletonPtr()->getGameClient();
			if (gc != 0)
			{
				gc->sendMessage(cm);
			}
			delete cm;
		}

	}
	void Chat::mnormal_EditBox_eventKeyButtonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char)
	{
		switch(_key.getValue())
		{
		case MyGUI::KeyCode::ArrowDown:
			{
				
				if (this->recorded_deque_text->size() >= _indexEditBoxArrows + 1)
				{
					_indexEditBoxArrows++;
					std::string str = this->recorded_deque_text->at(this->recorded_deque_text->size() - _indexEditBoxArrows);
					//this->mnormal_EditBox->addText(str);
					this->mnormal_EditBox->setCaption(str);
				}
				break;
			}

		case MyGUI::KeyCode::ArrowUp:
			{
				if (_indexEditBoxArrows - 1 > 0)
				{
					_indexEditBoxArrows--;
					if (this->recorded_deque_text->size() >= _indexEditBoxArrows)
					{
						std::string str = this->recorded_deque_text->at(this->recorded_deque_text->size() - _indexEditBoxArrows);
						this->mnormal_EditBox->setCaption(str);
					}
				}
				break;
			}
		default:
			{
				//_indexEditBoxArrows = 0;
				break;
			}
		}
	}

