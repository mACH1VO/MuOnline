#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class InventoryResponseMoveMessage : public GameMessage
{
public:
	InventoryResponseMoveMessage(void);
	~InventoryResponseMoveMessage(void);

	int ItemID; // Item's DynamicID
	int originWindowsID;
	int destinationWindowsID;
	int EquipmentSlot;
	int Column;
	int Row;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

