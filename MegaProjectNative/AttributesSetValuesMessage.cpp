#include "StdAfx.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
AttributesSetValuesMessage::AttributesSetValuesMessage(void)
{
	this->opcode = Opcodes::AttributesSetValuesMessage;
	this->consumer = Consumers::attribute_;
	this->nameClass = "AttributesSetValuesMessage";

	this->atKeyVals = new std::vector<NetAttributeKeyValue*>();
}


AttributesSetValuesMessage::~AttributesSetValuesMessage(void)
{
	delete this->atKeyVals;
}

void AttributesSetValuesMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->ActorID = buffer->ReadInt(32);

	int lengh = buffer->ReadInt(4);

	for (int i = 0; i < lengh; i++) 
	{ 
		atKeyVals->push_back(new NetAttributeKeyValue()); 
		atKeyVals->at(i)->Parse(buffer); 
	}

	for (int i = 0; i < lengh; i++) 
	{ 
		atKeyVals->at(i)->ParseValue(buffer); 
	}
}

void AttributesSetValuesMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, ActorID);

	buffer->WriteInt(4, atKeyVals->size());

	for (int i = 0; i < atKeyVals->size(); i++) 
	{ 
		atKeyVals->at(i)->Encode(buffer); 
	}

	for (int i = 0; i < atKeyVals->size(); i++) 
	{ 
		atKeyVals->at(i)->EncodeValue(buffer); 
	}
}

std::string AttributesSetValuesMessage::AsText()
{
	std::string b;
	/*int pad = 0;

	b.append("", pad);
	b.append("AttributesSetValuesMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("NewSceneId: " + Ogre::StringConverter::toString(this->NewSceneId) );
	b.append("", pad); b.append("Field1: " + Ogre::StringConverter::toString(this->Field1) );
	b.append("", --pad);
	b.append("}");*/
	return b;
}
};