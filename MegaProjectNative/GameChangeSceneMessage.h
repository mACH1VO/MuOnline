#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class GameChangeSceneMessage : public GameMessage
{
public:
	GameChangeSceneMessage(void);
	~GameChangeSceneMessage(void);

	int NewSceneId;
	int Field1;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

