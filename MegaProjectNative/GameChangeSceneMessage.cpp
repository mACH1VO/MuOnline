#include "StdAfx.h"
#include "GameChangeSceneMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"


namespace Messages
{
GameChangeSceneMessage::GameChangeSceneMessage(void)
{
	this->opcode = Opcodes::GameChangeSceneMessage;
	this->consumer = Consumers::Game_;
	this->nameClass = "GameChangeSceneMessage";
}


GameChangeSceneMessage::~GameChangeSceneMessage(void)
{

}

void GameChangeSceneMessage::Parse(Networking::GameBitBuffer* buffer)
{
	this->NewSceneId = buffer->ReadInt(32);
	this->Field1 = buffer->ReadInt(32);
}

void GameChangeSceneMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, NewSceneId);
	buffer->WriteInt(32, Field1);
}

std::string GameChangeSceneMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append("", pad);
	b.append("GameChangeSceneMessage:");
	b.append("", pad++);
	b.append("{");
	b.append("", pad); b.append("NewSceneId: " + Ogre::StringConverter::toString(this->NewSceneId) );
	b.append("", pad); b.append("Field1: " + Ogre::StringConverter::toString(this->Field1) );
	b.append("", --pad);
	b.append("}");
	return b;
}
};