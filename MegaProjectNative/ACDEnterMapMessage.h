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
class ACDEnterMapMessage : public GameMessage
{
public:
	ACDEnterMapMessage(void);
	~ACDEnterMapMessage(void);

	int ActorId;
	float Scale;
	Ogre::Vector3 Position;
	Ogre::Quaternion Orientation;
	int MapId;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

