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
class InventoryRequestBuyItemMessage : public GameMessage
{
public:
	InventoryRequestBuyItemMessage(void);
	~InventoryRequestBuyItemMessage(void);

	int DynamicID; // The actor's DynamicID

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

