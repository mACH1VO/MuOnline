#include "StdAfx.h"
#include "ACDDestroyActorMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
ACDDestroyActorMessage::ACDDestroyActorMessage(void)
{
	this->opcode = Opcodes::ACDDestroyActorMessage;
	this->consumer = Consumers::Factory;
	this->nameClass = "ACDDestroyActorMessage";
}


ACDDestroyActorMessage::~ACDDestroyActorMessage(void)
{

}

void ACDDestroyActorMessage::Parse(Networking::GameBitBuffer* buffer)
{
	DynamicID = buffer->ReadInt(32);
}

void ACDDestroyActorMessage::Encode(Networking::GameBitBuffer* buffer)
{
	throw "no need to use this";
}

std::string ACDDestroyActorMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("ACDDestroyActorMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ActorID: " + Ogre::StringConverter::toString(DynamicID) );
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};