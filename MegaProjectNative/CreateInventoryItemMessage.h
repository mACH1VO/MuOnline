#pragma once
#include "stdafx.h"
#include "GameMessage.h"
#include "MUEnums.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Game
{
	class InventorySlot;
}


namespace Messages
{
class CreateInventoryItemMessage : public GameMessage
{
public:
	CreateInventoryItemMessage(void);
	~CreateInventoryItemMessage(void);

	int ItemId;                                     
	int inventoryWindowId;                                    
	Game::InventorySlot* inventorySlot;                 
	int SNO;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

