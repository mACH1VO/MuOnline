#pragma once
#include "stdafx.h"


namespace Messages
{
	class GameMessage;
	class CreateInventoryItemMessage;
}
namespace Game
{
	class InventoryMessageHandler
	{
	public:
		InventoryMessageHandler(void);
		~InventoryMessageHandler(void);

		static void Consume(Messages::GameMessage* message);
	};
}
