#include "StdAfx.h"
#include "InventoryCloseWindowMessage.h"
#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
InventoryCloseWindowMessage::InventoryCloseWindowMessage(void)
{
	this->opcode = Opcodes::InventoryCloseWindowMessage;
	this->consumer = Consumers::Inventory;
	this->nameClass = "InventoryCloseWindowMessage";
}

InventoryCloseWindowMessage::~InventoryCloseWindowMessage(void)
{

}

void InventoryCloseWindowMessage::Parse(Networking::GameBitBuffer* buffer)
{
	windowId = buffer->ReadInt(32);
	visible = buffer->ReadBool();
}

void InventoryCloseWindowMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, windowId);
	buffer->WriteBool(visible);
}

std::string InventoryCloseWindowMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("InventoryCloseWindowMessage:");
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