#include "StdAfx.h"
#include "NetAttributeKeyValue.h"
#include "GameBitBuffer.h"
#include "MUEnums.h"
#include "AAttribute.h"
#include "AttributeValue.h"

#include "GameAttributeUtil.h"


namespace Messages
{
NetAttributeKeyValue::NetAttributeKeyValue(void)
{
}


NetAttributeKeyValue::~NetAttributeKeyValue(void)
{
}

void NetAttributeKeyValue::Parse(Networking::GameBitBuffer* buffer)
{
	 this->Index = buffer->ReadInt(10) & 0xFFF;
	 this->Attribute = Game::GameAttributeUtil::getSingletonPtr()->getAttribute(Index);
}
void NetAttributeKeyValue::ParseValue(Networking::GameBitBuffer* buffer)
{
	switch (Attribute->EncodingType)
	{
	case AttributeEncoding::Int:
		{
		this->Int = buffer->ReadInt(Attribute->BitCount);
		this->Attribute->_defaultValue = Game::AttributeValue(this->Int);
		break;
		}
	case AttributeEncoding::IntMinMax:
		{
		this->Int = buffer->ReadInt(Attribute->BitCount) + Attribute->Min.Value;
		this->Attribute->_defaultValue = Game::AttributeValue(this->Int);
		break;
		}
	case AttributeEncoding::Float16:
		{

		this->Float = buffer->ReadFloat16();
		this->Attribute->_defaultValue = Game::AttributeValue(this->Float);
		break;
		}
	case AttributeEncoding::Float16Or32:
		{
		this->Float = buffer->ReadBool() ? buffer->ReadFloat16() : buffer->ReadFloat32();
		this->Attribute->_defaultValue = Game::AttributeValue(this->Float);
		break;
		}
	case AttributeEncoding::Float32:
		{
		this->Float = buffer->ReadFloat32();
		this->Attribute->_defaultValue = Game::AttributeValue(this->Float);
		break;
		}
	default:
		OGRE_EXCEPT(Ogre::Exception::ExceptionCodes::ERR_ITEM_NOT_FOUND, "EncodingType not found, ParseValue", "NetAttributeKeyValue.cpp");
		break;
	}

	
}

void NetAttributeKeyValue::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(10, this->Attribute->Id);
}

void NetAttributeKeyValue::EncodeValue(Networking::GameBitBuffer* buffer)
{
	switch (Attribute->EncodingType)
	{
	case AttributeEncoding::Int:
		buffer->WriteInt(Attribute->BitCount, Int);
		break;
	case AttributeEncoding::IntMinMax:
		buffer->WriteInt(Attribute->BitCount, Int - Attribute->Min.Value);
		break;
	case AttributeEncoding::Float16:
		buffer->WriteFloat16(Float);
		break;
	case AttributeEncoding::Float16Or32:
		if (Float >= 65536.0f || -65536.0f >= Float)
		{
			buffer->WriteBool(false);
			buffer->WriteFloat32(Float);
		}
		else
		{
			buffer->WriteBool(true);
			buffer->WriteFloat16(Float);
		}
		break;
	case AttributeEncoding::Float32:
		buffer->WriteFloat32(Float);
		break;
	default:
		OGRE_EXCEPT(Ogre::Exception::ExceptionCodes::ERR_ITEM_NOT_FOUND, "EncodingType not found, EncodeValue", "NetAttributeKeyValue.cpp");
		break;
	}
}


void NetAttributeKeyValue::AsText(std::string b, int pad)
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