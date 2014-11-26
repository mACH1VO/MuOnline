#pragma once
#include "stdafx.h"
#include "GameMessage.h"
#include "MUEnums.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class ACDCreateActorMessage : public GameMessage
{
public:
	ACDCreateActorMessage(void);
	~ACDCreateActorMessage(void);

	int DynamicID; // The actor's DynamicID
	int ActorSNOId;
	ActorType actorType;
	int Field2;
	int Field3; 

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

