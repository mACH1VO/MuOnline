#pragma once
#include "stdafx.h"
//#include "MUEnums.h"


class GameBitBuffer;

enum Opcodes;
enum Consumers;
namespace Networking
{
	class GameBitBuffer;
}
namespace Messages
{
	
class GameMessage
{
public:
	GameMessage(void);
	~GameMessage(void);

	//int id;
	Opcodes opcode;
	Consumers consumer;
	std::string nameClass;

	static GameMessage* ParseMessage(Networking::GameBitBuffer* buffer);

	virtual void Parse(Networking::GameBitBuffer* buffer);
	virtual void Encode(Networking::GameBitBuffer* buffer);
	virtual std::string AsText();
};
};
