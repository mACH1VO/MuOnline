#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class NewPlayerMessage : public GameMessage
{
public:
	NewPlayerMessage(void);
	~NewPlayerMessage(void);

	int DynamicId;
	std::string ToonName;
	int Field3;
	int Field4;
	int /* sno */ snoActorPortrait;
	int Level;
	//public HeroStateData StateData;
	bool IsMainPlayer;
	int Field9;
	int SNO;
	int ActorID; // Hero's DynamicID

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

