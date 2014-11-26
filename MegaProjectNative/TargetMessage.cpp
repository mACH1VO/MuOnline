#include "StdAfx.h"
#include "TargetMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"
#include "Extension.h"


namespace Messages
{
TargetMessage::TargetMessage(void)
{
	this->opcode = Opcodes::TargetMessage;
	this->consumer = Consumers::Map;
	this->nameClass = "TargetMessage";
}

TargetMessage::~TargetMessage(void)
{

}

void TargetMessage::Parse(Networking::GameBitBuffer* buffer)
{
	Field0 = buffer->ReadInt(3) + (-1);
	TargetID = buffer->ReadInt(32);
	Position = Extension::ParseV3(buffer);
	PowerSlot = buffer->ReadInt(32);
	Field4 = buffer->ReadInt(32);
	Field5 = buffer->ReadInt(2);
}

void TargetMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(3, Field0 - (-1));
	buffer->WriteInt(32, TargetID);
	Extension::EncodeV3(Position, buffer);
	buffer->WriteInt(32, PowerSlot);
	buffer->WriteInt(32, Field4);
	buffer->WriteInt(2, Field5);
}

std::string TargetMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("TargetMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	/*b.append("ActorID: " + Ogre::StringConverter::toString(ActorId) );
	b.append(" ", pad); 
	b.append("Scale: " + Ogre::StringConverter::toString(Scale) );
	b.append(" ", pad); 
	b.append("Position: "  + Ogre::StringConverter::toString(Position) );
	b.append(" ", pad); 
	b.append("Orientation: " + Ogre::StringConverter::toString(Orientation) );
	b.append(" ", pad); 
	b.append("MapId: "  + Ogre::StringConverter::toString(MapId) );*/
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};