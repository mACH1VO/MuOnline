#include "StdAfx.h"
#include "Factory.h"
#include "MUEnums.h"

#include "GameMessage.h"
#include "NewPlayerMessage.h"
#include "ACDCreateActorMessage.h"
#include "ACDDestroyActorMessage.h"

#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Item.h"
#include "Map.h"


template<> Game::Factory* Ogre::Singleton<Game::Factory>::msSingleton = 0;

namespace Game
{


Factory::Factory(void)
{
	this->pendingActorsMap = new std::map<int, Actor*>();
}

Factory::~Factory(void)
{
	delete this->pendingActorsMap;
}

void Factory::destroyActor(Messages::ACDDestroyActorMessage* destroyActorMsg)
{
	Actor* actor = Map::getSingletonPtr()->actorMap->at(destroyActorMsg->DynamicID);
	Map::getSingletonPtr()->LeaveActor(actor);
	//Map::getSingletonPtr()->actorMap->erase(destroyActorMsg->DynamicID);
	switch(actor->getActorType())
			{

			case ActorType::Player:
				{
					Player* p = (Player*)actor;
					delete p;
					break;
				}
			case ActorType::Monster:
				{
					Monster* m = (Monster*)actor;
					delete m;
					break;
				}

			case ActorType::Item:
				{
					Item* i = (Item*)actor;
					delete i;
					break;
				}
			case ActorType::NPC:
				{
					NPC* npc = (NPC*)actor;
					delete npc;
					break;
				}
			default:
				{
					LogManager::getSingletonPtr()->logMessage("[Factory] Consume error in Factory, ACDDestroyActorMessage->actorType id not recognized");
					break;
				}
			}
}

void Factory::Consume(Messages::GameMessage* message)
{
	//LogManager::getSingletonPtr()->logMessage(" /////// Factory --" + message->nameClass);
	switch((Opcodes)message->opcode)
	{
	case Opcodes::NewPlayerMessage:
		{
			Messages::NewPlayerMessage* newPlayerMessage = (Messages::NewPlayerMessage*)message;
			Game::Player* p = new Game::Player(newPlayerMessage->SNO, newPlayerMessage->DynamicId, newPlayerMessage->IsMainPlayer);
			int did = p->dynamicId;
			this->pendingActorsMap->insert(std::make_pair(p->dynamicId, (Game::Actor*)p));
			//this->pendingActorsMap[p->dynamicId] = (Game::Actor*)p;
			break;
		}
	case Opcodes::ACDCreateActorMessage:
		{
			Messages::ACDCreateActorMessage* createActorMsg = (Messages::ACDCreateActorMessage*)message;
			switch(createActorMsg->actorType)
			{

			case ActorType::Monster:
				{
					//Monster* m = this->createMonster(createActorMsg);
					Game::Monster* m = new Game::Monster(createActorMsg->ActorSNOId, createActorMsg->DynamicID);
					this->pendingActorsMap->insert(std::make_pair(m->dynamicId, m));
					break;
				}

			case ActorType::Item:
				{
					Game::Item* i = new Game::Item(createActorMsg->ActorSNOId, createActorMsg->DynamicID);
					this->pendingActorsMap->insert(std::make_pair(i->dynamicId, i));
					break;
				}
			case ActorType::NPC:
				{
					Game::NPC* i = new Game::NPC(createActorMsg->ActorSNOId, createActorMsg->DynamicID);
					this->pendingActorsMap->insert(std::make_pair(i->dynamicId, i));
					break;
				}
			default:
				{
					LogManager::getSingletonPtr()->logMessage("[Factory] Consume error in Factory, ACDCreateActorMessage->actorType id not recognized");
					break;
				}
			}
			break;
		}
	case Opcodes::ACDDestroyActorMessage:
		{
			Messages::ACDDestroyActorMessage* destroyActorMsg = (Messages::ACDDestroyActorMessage*)message;
			this->destroyActor(destroyActorMsg);
			break;
		}
	default:
		{
			LogManager::getSingletonPtr()->logMessage("[Factory] Consume error in Factory, opcode id not recognized, id opcode = " + Ogre::StringConverter::toString((int)message->opcode));
			break;
		}
	}
}

}
