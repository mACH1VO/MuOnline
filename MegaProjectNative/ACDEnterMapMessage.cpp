#include "StdAfx.h"
#include "ACDEnterMapMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"
#include "Extension.h"


namespace Messages
{
ACDEnterMapMessage::ACDEnterMapMessage(void)
{
	this->opcode = Opcodes::ACDEnterMapMessage;
	this->consumer = Consumers::Map;
	this->nameClass = "ACDEnterMapMessage";
}


ACDEnterMapMessage::~ACDEnterMapMessage(void)
{

}

void ACDEnterMapMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ActorId = buffer->ReadInt(32);
	Scale = buffer->ReadFloat32();
	Position = Extension::ParseV3(buffer);
	//Position = Position.Parse(buffer);
	Orientation = Extension::ParseQ(buffer);
	//Orientation = Orientation.Parse(buffer);
	MapId = buffer->ReadInt(32);
}

void ACDEnterMapMessage::Encode(Networking::GameBitBuffer* buffer)
{
	throw "no need to use this";
}

std::string ACDEnterMapMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("ACDEnterMapMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ActorID: " + Ogre::StringConverter::toString(ActorId) );
	b.append(" ", pad); 
	b.append("Scale: " + Ogre::StringConverter::toString(Scale) );
	b.append(" ", pad); 
	b.append("Position: "  + Ogre::StringConverter::toString(Position) );
	b.append(" ", pad); 
	b.append("Orientation: " + Ogre::StringConverter::toString(Orientation) );
	b.append(" ", pad); 
	b.append("MapId: "  + Ogre::StringConverter::toString(MapId) );
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};