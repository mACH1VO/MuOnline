#include "StdAfx.h"
#include "ChatMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"

namespace Messages
{
ChatMessage::ChatMessage(void)
{
	this->opcode = Opcodes::ChatMessage;
	this->consumer = Consumers::__Chat;
	this->nameClass = "ChatMessage";
}


ChatMessage::~ChatMessage(void)
{

}

void ChatMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ActorDynamicID = buffer->ReadInt(32);
	Type = buffer->ReadInt(2);
	Lengh = buffer->ReadInt(4) + (-1);
	Text = buffer->ReadCharArray(512);
}

void ChatMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ActorDynamicID);
	buffer->WriteInt(2, Type);
	buffer->WriteInt(4, Lengh - (-1));
	buffer->WriteCharArray(512, Text);
}

std::string ChatMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("ChatMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("ActorDynamicID: "  + Ogre::StringConverter::toString(this->ActorDynamicID) );
	b.append("", pad); b.append("Field0: " + Ogre::StringConverter::toString(this->Type) );
	b.append("", pad); b.append("Field1: " + Ogre::StringConverter::toString( Lengh ) );
	b.append("", pad); b.append("Field2: \"" + Text + "\"");
	b.append("", --pad);
	b.append("}");
	return b;
}
};