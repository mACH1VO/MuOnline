#include "StdAfx.h"
#include "ACDCreateActorMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
ACDCreateActorMessage::ACDCreateActorMessage(void)
{
	this->opcode = Opcodes::ACDCreateActorMessage;
	this->consumer = Consumers::Factory;
	this->nameClass = "ACDCreateActorMessage";
}


ACDCreateActorMessage::~ACDCreateActorMessage(void)
{

}

void ACDCreateActorMessage::Parse(Networking::GameBitBuffer* buffer)
{
	DynamicID = buffer->ReadInt(32);
	ActorSNOId = buffer->ReadInt(32);
	this->actorType = (ActorType)buffer->ReadInt(32);
	Field2 = buffer->ReadInt(6);
	Field3 = buffer->ReadInt(2) + (-1);
}

void ACDCreateActorMessage::Encode(Networking::GameBitBuffer* buffer)
{
	throw "no need to use this";
}

std::string ACDCreateActorMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("ACDCreateActorMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ActorID: " + Ogre::StringConverter::toString(DynamicID) );
	b.append(" ", pad); 
	b.append("ActorSNOId: " + Ogre::StringConverter::toString(ActorSNOId) );
	b.append(" ", pad); 
	b.append("ActorType: "  + Ogre::StringConverter::toString((int)this->actorType) );
	b.append(" ", pad); 
	b.append("Field2: " + Ogre::StringConverter::toString(Field2) );
	b.append(" ", pad); 
	b.append("Field3: "  + Ogre::StringConverter::toString(Field3) );
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};