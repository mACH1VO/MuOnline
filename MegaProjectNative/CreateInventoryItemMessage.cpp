#include "StdAfx.h"
#include "CreateInventoryItemMessage.h"

#include "Item.h"
#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
CreateInventoryItemMessage::CreateInventoryItemMessage(void)
{
	this->opcode = Opcodes::CreateInventoryItemMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "CreateInventoryItemMessage";
}

CreateInventoryItemMessage::~CreateInventoryItemMessage(void)
{
	delete this->inventorySlot;
}

void CreateInventoryItemMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ItemId = buffer->ReadInt(32);
	inventoryWindowId = buffer->ReadInt(32);
	inventorySlot = new Game::InventorySlot();
	this->inventorySlot->Parse(buffer);
	SNO = buffer->ReadInt(32);
}

void CreateInventoryItemMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ItemId);
	buffer->WriteInt(32, inventoryWindowId);
	this->inventorySlot->Encode(buffer);
	buffer->WriteInt(32, SNO);
}

std::string CreateInventoryItemMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("CreateInventoryItemMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("ItemId: "  + ItemId );
	b.append("", pad); b.append("OwnerID: " + inventoryWindowId );
	this->inventorySlot->AsText(b, pad);
	b.append("", pad); b.append("SNO: " + SNO );
	b.append("", --pad);
	b.append("}");
	return b;
}
};