#include "StdAfx.h"
#include "InventoryShowWindowMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
InventoryShowWindowMessage::InventoryShowWindowMessage(void)
{
	this->opcode = Opcodes::InventoryShowWindowMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryShowWindowMessage";
}


InventoryShowWindowMessage::~InventoryShowWindowMessage(void)
{

}

void InventoryShowWindowMessage::Parse(Networking::GameBitBuffer* buffer)
{
	windowId = buffer->ReadInt(32);
	visible = buffer->ReadBool();
}

void InventoryShowWindowMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, windowId);
	buffer->WriteBool(visible);
}

std::string InventoryShowWindowMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("InventoryShowWindowMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("windowId: " + Ogre::StringConverter::toString(windowId) );
	b.append("visible: " + Ogre::StringConverter::toString(visible) );
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};