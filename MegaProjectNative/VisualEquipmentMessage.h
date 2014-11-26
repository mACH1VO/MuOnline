#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class VisualItem;
class VisualEquipmentMessage : public GameMessage
{
public:
	VisualEquipmentMessage(void);
	~VisualEquipmentMessage(void);

	int ActorID;
	std::vector<VisualItem>* Equipment;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

