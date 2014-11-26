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
class AvailableSkillListMessage : public GameMessage
{
public:
	AvailableSkillListMessage(void);
	~AvailableSkillListMessage(void);

	int _lengh;
	std::vector<int>* availableSkillList;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

