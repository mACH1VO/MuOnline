#include "StdAfx.h"
#include "InventoryRequestMoveMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"

namespace Messages
{
InventoryRequestMoveMessage::InventoryRequestMoveMessage(void)
{
	this->opcode = Opcodes::InventoryRequestMoveMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryRequestMoveMessage";
}


InventoryRequestMoveMessage::~InventoryRequestMoveMessage(void)
{

}

void InventoryRequestMoveMessage::Parse(Networking::GameBitBuffer* buffer)
{
	ItemID = buffer->ReadInt(32);
	inventoryWindowId = buffer->ReadInt(32);
	EquipmentSlot = buffer->ReadInt(5) + (-1);
	Column = buffer->ReadInt(32);
	Row = buffer->ReadInt(32);
}

void InventoryRequestMoveMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ItemID);
	buffer->WriteInt(32, inventoryWindowId);
	buffer->WriteInt(5, EquipmentSlot - (-1));
	buffer->WriteInt(32, Column);
	buffer->WriteInt(32, Row);
}

std::string InventoryRequestMoveMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("InventoryRequestMoveMessage:");
	/*b.Append(' ', pad++);
	b.AppendLine("{");
	b.Append(' ', pad); b.AppendLine("ItemID: 0x" + ItemID.ToString("X8") + " (" + ItemID + ")");
	b.Append(' ', pad);
	b.AppendLine("InvLoc:");
	b.Append(' ', pad++);
	b.AppendLine("{");
	b.Append(' ', pad);
	b.AppendLine("inventoryWindowId: 0x" + OwnerID.ToString("X8") + " (" + OwnerID + ")");
	b.Append(' ', pad);
	b.AppendLine("EquipmentSlot: 0x" + EquipmentSlot.ToString("X8") + " (" + EquipmentSlot + ")");
	b.Append(' ', pad);
	b.AppendLine("Column: 0x" + Column.ToString("X8") + " (" + Column + ")");
	b.Append(' ', pad);
	b.AppendLine("Row: 0x" + Row.ToString("X8") + " (" + Row + ")");
	b.Append(' ', --pad);
	b.AppendLine("}");
	b.Append(' ', --pad);
	b.AppendLine("}");*/
	return b;
}
};