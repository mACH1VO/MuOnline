#include "StdAfx.h"
#include "VisualEquipmentMessage.h"
#include "VisualItem.h"
#include "GameBitBuffer.h"
#include "MUEnums.h"

namespace Messages
{
VisualEquipmentMessage::VisualEquipmentMessage(void)
{
	this->opcode = Opcodes::VisualEquipmentMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "VisualEquipmentMessage";

	this->Equipment = new std::vector<VisualItem>();
}


VisualEquipmentMessage::~VisualEquipmentMessage(void)
{
	delete this->Equipment;
}

void VisualEquipmentMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ActorID = buffer->ReadInt(32);
	for (int i = 0; i < 9; i++)
	{
		this->Equipment->push_back(VisualItem());
		this->Equipment->at(i).Parse(buffer);
	}
}

void VisualEquipmentMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteUInt(32, ActorID);
	for (int i = 0; i < Equipment->size(); i++)
	{
		this->Equipment->at(i).Encode(buffer);
	}
}

std::string VisualEquipmentMessage::AsText()
{
	std::string b;
	int pad = 0;

	/*b.append("", pad);
	b.append("VisualEquipmentMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("ActorDynamicID: "  + Ogre::StringConverter::toString(this->ActorDynamicID) );
	b.append("", pad); b.append("Field0: " + Ogre::StringConverter::toString(this->Type) );
	b.append("", pad); b.append("Field1: " + Ogre::StringConverter::toString( Lengh ) );
	b.append("", pad); b.append("Field2: \"" + Text + "\"");
	b.append("", --pad);
	b.append("}");*/
	return b;
}
}