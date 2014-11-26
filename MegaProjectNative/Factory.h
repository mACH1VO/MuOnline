#pragma once
#include "StdAfx.h"

namespace Messages
{
	class GameMessage;
	class NewPlayerMessage;
	class ACDCreateActorMessage;
	class ACDDestroyActorMessage;
}

namespace Game
{

class Map;
class Player;
class Monster;
class Actor;
class Item;

//enum ActorType;

class Factory : public Ogre::Singleton<Factory>
{
public:
	Factory(void);
	~Factory(void);

	std::map<int ,Actor*>* pendingActorsMap;

	void Consume(Messages::GameMessage* message);

	void destroyActor(Messages::ACDDestroyActorMessage* destroyActorMsg);
};
}
