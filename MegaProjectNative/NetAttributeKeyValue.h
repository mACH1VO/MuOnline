#pragma once
#include "stdafx.h"

namespace Networking
{
	class GameBitBuffer;
}
namespace Game
{
	class AAttribute;
}
namespace Messages
{
class NetAttributeKeyValue
{
public:
	NetAttributeKeyValue(void);
	~NetAttributeKeyValue(void);

	Game::AAttribute* Attribute;
	int Index;
	int Int;
	float Float;

	void NetAttributeKeyValue::Parse(Networking::GameBitBuffer* buffer);
	void NetAttributeKeyValue::Encode(Networking::GameBitBuffer* buffer);

	void NetAttributeKeyValue::ParseValue(Networking::GameBitBuffer* buffer);
	void NetAttributeKeyValue::EncodeValue(Networking::GameBitBuffer* buffer);


	void NetAttributeKeyValue::AsText(std::string b, int pad);
};
};

