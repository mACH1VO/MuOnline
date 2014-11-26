#include "StdAfx.h"
#include "VisualItem.h"
#include "GameBitBuffer.h"


namespace Messages
{
VisualItem::VisualItem(void)
{
}


VisualItem::~VisualItem(void)
{
}

void VisualItem::Parse(Networking::GameBitBuffer* buffer)
{
	snoId = buffer->ReadInt(32);
	SlotID = buffer->ReadInt(5);
	Field2 = buffer->ReadInt(4);
	Field3 = buffer->ReadInt(5) + (-1);
}

void VisualItem::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, snoId);
	buffer->WriteInt(5, SlotID);
	buffer->WriteInt(4, Field2);
	buffer->WriteInt(5, Field3 - (-1));
}

void VisualItem::AsText(std::string b, int pad)
{
	/*b.append(' ', pad);
	b.append("InventorySlot:");
	b.append(' ', pad++);
	b.append("{");
	b.append(' ', pad);
	b.append("R: " + Ogre::StringConverter::toString(R));
	b.append(' ', pad);
	b.append("C: " + Ogre::StringConverter::toString(C));
	b.append(' ', --pad);
	b.append("}");*/
}
}