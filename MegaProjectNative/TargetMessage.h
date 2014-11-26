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
class TargetMessage : public GameMessage
{
public:
	TargetMessage(void);
	~TargetMessage(void);

	int Field0;
	int TargetID; // Targeted actor's DynamicID
	Ogre::Vector3 Position;
	int PowerSlot; //slot
	int Field4;
	int Field5;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

