#include "StdAfx.h"
#include "AvailableSkillListMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"
#include "Extension.h"


namespace Messages
{
AvailableSkillListMessage::AvailableSkillListMessage(void)
{
	this->opcode = Opcodes::AvailableSkillListMessage;
	this->consumer = Consumers::Player_;
	this->nameClass = "AvailableSkillListMessage";

	this->availableSkillList = new std::vector<int>();
}

AvailableSkillListMessage::~AvailableSkillListMessage(void)
{
	delete this->availableSkillList;
}

void AvailableSkillListMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->_lengh = buffer->ReadInt(4);
	for (int i = 0; i < this->_lengh; i++)
	{
		int skillOpcode = buffer->ReadInt(32);
		this->availableSkillList->push_back(skillOpcode);
	}
}

void AvailableSkillListMessage::Encode(Networking::GameBitBuffer* buffer)
{
	OGRE_EXCEPT(Ogre::Exception::ExceptionCodes::ERR_NOT_IMPLEMENTED, "", "");
}

std::string AvailableSkillListMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("AvailableSkillListMessage:");
	b.append(" ", pad++);
	b.append("{"); 
	b.append(" ", pad); 
	b.append("Lengh: "  + Ogre::StringConverter::toString(this->_lengh) );
	b.append(" ", pad); 
	for (int i = 0; i < this->_lengh; i++)
	{
		b.append("skillOpcode: "  + Ogre::StringConverter::toString( this->availableSkillList->at(i)) );
		b.append(" ", pad); 
	}
	b.append(" ", --pad);
	b.append("}");
	return b;
}
};