#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class ChatMessage : public GameMessage
{
public:
	ChatMessage(void);
	~ChatMessage(void);

	int ActorDynamicID;
	int Type;
	int Lengh;
	string Text;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

