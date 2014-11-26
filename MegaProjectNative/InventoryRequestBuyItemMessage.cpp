#include "StdAfx.h"
#include "InventoryRequestBuyItemMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
InventoryRequestBuyItemMessage::InventoryRequestBuyItemMessage(void)
{
	this->opcode = Opcodes::InventoryRequestBuyItemMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryRequestBuyItemMessage";
}


InventoryRequestBuyItemMessage::~InventoryRequestBuyItemMessage(void)
{

}

void InventoryRequestBuyItemMessage::Parse(Networking::GameBitBuffer* buffer)
{
	DynamicID = buffer->ReadInt(32);
}

void InventoryRequestBuyItemMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, this->DynamicID);
}

std::string InventoryRequestBuyItemMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("InventoryRequestBuyItemMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("ActorID: " + Ogre::StringConverter::toString(DynamicID) );
	b.append(" ", --pad);
	b.append("}");

	return b;
}
};