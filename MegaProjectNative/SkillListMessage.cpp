#include "StdAfx.h"
#include "SkillListMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
SkillListMessage::SkillListMessage(void)
{
	this->opcode = Opcodes::SkillListMessage;
	this->consumer = Consumers::Player_;
	this->nameClass = "SkillListMessage";
}


SkillListMessage::~SkillListMessage(void)
{

}

void SkillListMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->Primary = (SkillOpcode)buffer->ReadInt(32);
	this->Secondary = (SkillOpcode)buffer->ReadInt(32);

	this->_one = (SkillOpcode)buffer->ReadInt(32);
	this->_two = (SkillOpcode)buffer->ReadInt(32);
	this->_three = (SkillOpcode)buffer->ReadInt(32);
	this->_four = (SkillOpcode)buffer->ReadInt(32);
}

void SkillListMessage::Encode(Networking::GameBitBuffer* buffer)
{
	throw "no need to use this";
}

std::string SkillListMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(" ", pad);
	b.append("SkillListMessage:");
	b.append(" ", pad++);
	b.append("{");
	b.append(" ", pad); 
	b.append("Primary: " + Ogre::StringConverter::toString(Primary) );
	b.append(" ", pad); 
	b.append("Secondary: " + Ogre::StringConverter::toString(Secondary) );
	b.append(" ", pad); 
	b.append("_one: "  + Ogre::StringConverter::toString(this->_one) );
	b.append(" ", pad); 
	b.append("_two: " + Ogre::StringConverter::toString(_two) );
	b.append(" ", pad); 
	b.append("_three: "  + Ogre::StringConverter::toString(_three) );
	b.append(" ", --pad);
	b.append(" ", pad); 
	b.append("_four: "  + Ogre::StringConverter::toString(_four) );
	b.append("}");
	return b;
}
};