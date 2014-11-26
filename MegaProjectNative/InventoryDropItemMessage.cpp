#include "StdAfx.h"
#include "InventoryDropItemMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
InventoryDropItemMessage::InventoryDropItemMessage(void)
{
	this->opcode = Opcodes::InventoryDropItemMessage;
	this->consumer = Consumers::Factory;
	this->nameClass = "InventoryDropItemMessage";
}


InventoryDropItemMessage::~InventoryDropItemMessage(void)
{

}

void InventoryDropItemMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ItemID = buffer->ReadInt(32);
}

void InventoryDropItemMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ItemID);
}

std::string InventoryDropItemMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("InventoryDropItemMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ItemID: " + Ogre::StringConverter::toString(ItemID) );
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};