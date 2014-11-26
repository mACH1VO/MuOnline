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
class ACDClientTranslateMessage : public GameMessage
{
public:
	ACDClientTranslateMessage(void);
	~ACDClientTranslateMessage(void);

	Ogre::Vector3 Position;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

