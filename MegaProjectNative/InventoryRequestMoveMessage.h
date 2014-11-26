#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class InventoryRequestMoveMessage : public GameMessage
{
public:
	InventoryRequestMoveMessage(void);
	~InventoryRequestMoveMessage(void);

	int ItemID; // Item's DynamicID
	int inventoryWindowId; 
	int EquipmentSlot;
	int Column;
	int Row;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

