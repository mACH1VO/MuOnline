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
class InventoryDropItemMessage : public GameMessage
{
public:
	InventoryDropItemMessage(void);
	~InventoryDropItemMessage(void);

	int ItemID; // The items's DynamicID

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

