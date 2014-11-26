#include "StdAfx.h"
#include "DestroyInventoryItemMessage.h"

#include "Item.h"
#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
DestroyInventoryItemMessage::DestroyInventoryItemMessage(void)
{
	this->opcode = Opcodes::DestroyInventoryItemMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "DestroyInventoryItemMessage";
}

DestroyInventoryItemMessage::~DestroyInventoryItemMessage(void)
{
	delete this->inventorySlot;
}

void DestroyInventoryItemMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ItemId = buffer->ReadInt(32);
	inventoryWindowId = buffer->ReadInt(32);
	inventorySlot = new Game::InventorySlot();
	this->inventorySlot->Parse(buffer);
	SNO = buffer->ReadInt(32);
}

void DestroyInventoryItemMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ItemId);
	buffer->WriteInt(32, inventoryWindowId);
	this->inventorySlot->Encode(buffer);
	buffer->WriteInt(32, SNO);
}

std::string DestroyInventoryItemMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("DestroyInventoryItemMessage:");
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