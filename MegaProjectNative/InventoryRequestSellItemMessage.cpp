#include "StdAfx.h"
#include "InventoryRequestSellItemMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"

namespace Messages
{
InventoryRequestSellItemMessage::InventoryRequestSellItemMessage(void)
{
	this->opcode = Opcodes::InventoryRequestSellItemMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryRequestSellItemMessage";
}

InventoryRequestSellItemMessage::~InventoryRequestSellItemMessage(void)
{

}

void InventoryRequestSellItemMessage::Parse(Networking::GameBitBuffer* buffer)
{
	DynamicID = buffer->ReadInt(32);
}

void InventoryRequestSellItemMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, this->DynamicID);
}

std::string InventoryRequestSellItemMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("InventoryRequestSellItemMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ActorID: " + Ogre::StringConverter::toString(DynamicID) );
	b.append(" ", --pad);
	b.append("}");

	return b;
}
};