#include "StdAfx.h"
#include "GameSetupMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
GameSetupMessage::GameSetupMessage(void)
{
	this->opcode = Opcodes::GameSetupMessage;
	this->consumer = Consumers::Game_;
	this->nameClass = "GameSetupMessage";
}


GameSetupMessage::~GameSetupMessage(void)
{

}

void GameSetupMessage::Parse(Networking::GameBitBuffer* buffer)
{
	//this->Field0 = buffer->ReadInt(32);
	this->Field0 = buffer->ReadFloat32();
}

void GameSetupMessage::Encode(Networking::GameBitBuffer* buffer)
{
	//buffer->WriteInt(32, Field0);
	buffer->WriteFloat32(Field0);
}

std::string GameSetupMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("GameSetupMessage: ");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("Field0: " + Ogre::StringConverter::toString(this->Field0) );
	b.append("", --pad);
	b.append("}");
	return b;
}

};