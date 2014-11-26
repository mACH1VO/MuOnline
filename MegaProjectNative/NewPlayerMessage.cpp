#include "StdAfx.h"
#include "NewPlayerMessage.h"

#include "GameBitBuffer.h"
#include "MUEnums.h"



namespace Messages
{
NewPlayerMessage::NewPlayerMessage(void)
{
	this->opcode = Opcodes::NewPlayerMessage;
	this->consumer = Consumers::Factory;
	this->nameClass = "NewPlayerMessage";
}


NewPlayerMessage::~NewPlayerMessage(void)
{

}

void NewPlayerMessage::Parse(Networking::GameBitBuffer* buffer)
{
	DynamicId = buffer->ReadInt(32);
	ToonName = buffer->ReadCharArray(49);
	Field3 = buffer->ReadInt(5) + (-1);
	Field4 = buffer->ReadInt(3) + (-1);
	snoActorPortrait = buffer->ReadInt(32);
	Level = buffer->ReadInt(7);
	//StateData = new HeroStateData();
	//StateData.Parse(buffer);
	IsMainPlayer = buffer->ReadBool();
	Field9 = buffer->ReadInt(32);
	SNO = buffer->ReadInt(32);
	ActorID = buffer->ReadInt(32);
}

void NewPlayerMessage::Encode(Networking::GameBitBuffer* buffer)
{
	buffer->WriteInt(32, DynamicId);
	buffer->WriteCharArray(49, ToonName);
	buffer->WriteInt(5, Field3 - (-1));
	buffer->WriteInt(3, Field4 - (-1));
	buffer->WriteInt(32, snoActorPortrait);
	buffer->WriteInt(7, Level);
	//StateData.Encode(buffer);
	buffer->WriteBool(IsMainPlayer);
	buffer->WriteInt(32, Field9);
	buffer->WriteInt(32, SNO);
	buffer->WriteInt(32, ActorID);
}

std::string NewPlayerMessage::AsText()
{
	std::string b;
	int pad = 0;

	b.append(' ', pad);
	b.append("NewPlayerMessage:");
	b.append(' ', pad++);
	b.append("{");
	b.append(' ', pad); b.append("DynamicId: " + Ogre::StringConverter::toString(DynamicId) );
	b.append(' ', pad); b.append("ToonName: \"" + (ToonName));
	b.append(' ', pad); b.append("Field3: " + Ogre::StringConverter::toString(Field3) );
	b.append(' ', pad); b.append("Field4: " + Ogre::StringConverter::toString(Field4) );
	b.append(' ', pad); b.append("snoActorPortrait: " + snoActorPortrait);
	b.append(' ', pad); b.append("Level: " + Level);
	//StateData.AsText(b, pad);
	b.append(' ', pad); b.append("IsMainPlayer: " + Ogre::StringConverter::toString(IsMainPlayer));
	b.append(' ', pad); b.append("Field9: " + Ogre::StringConverter::toString(Field9) );
	b.append(' ', pad); b.append("SNO: " + Ogre::StringConverter::toString(SNO) );
	b.append(' ', pad); b.append("ActorID: " + Ogre::StringConverter::toString(ActorID));
	b.append(' ', --pad);
	b.append("}");

	return b;
}
};