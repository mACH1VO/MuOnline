#include "StdAfx.h"
#include "ACDClientTranslateMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"
#include "Extension.h"


namespace Messages
{
ACDClientTranslateMessage::ACDClientTranslateMessage(void)
{
	this->opcode = Opcodes::ACDClientTranslateMessage;
	this->consumer = Consumers::Player_;
	this->nameClass = "ACDClientTranslateMessage";
}

ACDClientTranslateMessage::~ACDClientTranslateMessage(void)
{

}

void ACDClientTranslateMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->Position = Extension::ParseV3(buffer);
}

void ACDClientTranslateMessage::Encode(Networking::GameBitBuffer* buffer)
{
	Extension::EncodeV3(this->Position, buffer);
}

std::string ACDClientTranslateMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("ACDEnterMapMessage:");
	b.append(" ", pad++);
	b.append("{"); 
	b.append(" ", pad); 
	b.append("Position: "  + Ogre::StringConverter::toString(Position) );
	b.append(" ", pad); 
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};