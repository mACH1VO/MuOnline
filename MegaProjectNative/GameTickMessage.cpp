#include "StdAfx.h"
#include "GameTickMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"

namespace Messages
{
GameTickMessage::GameTickMessage(void)
{
	this->opcode = Opcodes::GameTickMessage;
	this->consumer = Consumers::Game_;
	this->nameClass = "GameTickMessage";
}


GameTickMessage::~GameTickMessage(void)
{

}

void GameTickMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->Tick = buffer->ReadInt(32);
}

void GameTickMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, Tick);
}

std::string GameTickMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("GameTickMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("Tick: " + Ogre::StringConverter::toString(this->Tick) );
	b.append("", --pad);
	b.append("}");
	return b;
}
};