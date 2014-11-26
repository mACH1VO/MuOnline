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
class InventoryRequestSellItemMessage : public GameMessage
{
public:
	InventoryRequestSellItemMessage(void);
	~InventoryRequestSellItemMessage(void);

	int DynamicID; // The actor's DynamicID

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

