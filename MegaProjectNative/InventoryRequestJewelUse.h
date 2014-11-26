#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class InventoryRequestJewelUse : public GameMessage
{
public:
	InventoryRequestJewelUse(void);
	~InventoryRequestJewelUse(void);

	int sourceJewelId;
	int destItemId;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

