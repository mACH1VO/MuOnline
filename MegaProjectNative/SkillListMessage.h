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
class SkillListMessage : public GameMessage
{
public:
	SkillListMessage(void);
	~SkillListMessage(void);

	SkillOpcode Primary;
	SkillOpcode Secondary;

	SkillOpcode _one;
	SkillOpcode _two;
	SkillOpcode _three; 
	SkillOpcode _four;

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};

