#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class GameTickMessage : public GameMessage
{
public:
	GameTickMessage(void);
	~GameTickMessage(void);

	int Tick;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

