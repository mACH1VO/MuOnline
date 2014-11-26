#include "StdAfx.h"
#include "AssignStatMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
AssignStatMessage::AssignStatMessage(void)
{
	this->opcode = Opcodes::AssignStatMessage;
	this->consumer = Consumers::Game_;
	this->nameClass = "AssignStatMessage";
}


AssignStatMessage::~AssignStatMessage(void)
{

}

void AssignStatMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->StatType = buffer->ReadInt(32);
}

void AssignStatMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, StatType);
}

std::string AssignStatMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("AssignStatMessage: ");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("StatType: " + Ogre::StringConverter::toString(this->StatType) );
	b.append("", --pad);
	b.append("}");
	return b;
}

};