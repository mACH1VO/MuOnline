#include "StdAfx.h"
#include "InventoryRequestJewelUse.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
InventoryRequestJewelUse::InventoryRequestJewelUse(void)
{
	this->opcode = Opcodes::InventoryRequestJewelUse;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryRequestJewelUse";
}


InventoryRequestJewelUse::~InventoryRequestJewelUse(void)
{

}

void InventoryRequestJewelUse::Parse(Networking::GameBitBuffer* buffer)
{
	this->sourceJewelId = buffer->ReadInt(32);
	this->destItemId = buffer->ReadInt(32);
}

void InventoryRequestJewelUse::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, sourceJewelId);
	buffer->WriteInt(32, destItemId);
}

std::string InventoryRequestJewelUse::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("InventoryRequestJewelUse:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("sourceJewelId: " + Ogre::StringConverter::toString(this->sourceJewelId) );
	b.append("", pad); b.append("destItemId: " + Ogre::StringConverter::toString(this->destItemId) );
	b.append("", --pad);
	b.append("}");
	return b;
}
};