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
class InventoryCloseWindowMessage : public GameMessage
{
public:
	InventoryCloseWindowMessage(void);
	~InventoryCloseWindowMessage(void);

	int windowId; // The items's DynamicID
	bool visible;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

