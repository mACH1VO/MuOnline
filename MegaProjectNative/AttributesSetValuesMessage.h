#pragma once
#include "stdafx.h"
#include "GameMessage.h"

namespace Networking
{
	class GameBitBuffer;
}

namespace Messages
{
class NetAttributeKeyValue;

class AttributesSetValuesMessage : public GameMessage
{
public:
	AttributesSetValuesMessage(void);
	~AttributesSetValuesMessage(void);

	int ActorID;
	std::vector<NetAttributeKeyValue*> *atKeyVals;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

