#pragma once
#include "StdAfx.h"
#include "GameMessage.h"
#include "GameBitBuffer.h"

#include "GameSetupMessage.h"
#include "GameTickMessage.h"
#include "GameChangeSceneMessage.h"
#include "NewPlayerMessage.h"
#include "ACDClientTranslateMessage.h"
#include "ACDCreateActorMessage.h"
#include "ACDDestroyActorMessage.h"
#include "ACDEnterMapMessage.h"
#include "ChatMessage.h"
#include "TargetMessage.h"
#include "CreateInventoryItemMessage.h"
#include "DestroyInventoryItemMessage.h"
#include "InventoryRequestMoveMessage.h"
#include "InventoryResponseMoveMessage.h"
#include "InventoryDropItemMessage.h"
#include "InventoryShowWindowMessage.h"
#include "InventoryCloseWindowMessage.h"
#include "InventoryRequestJewelUse.h"
#include "VisualEquipmentMessage.h"
#include "AttributesSetValuesMessage.h"

#include "SkillListMessage.h"
#include "AvailableSkillListMessage.h"


#include "MUEnums.h"

namespace Messages
{

GameMessage::GameMessage(void)
{

}


GameMessage::~GameMessage(void)
{

}

void GameMessage::Parse(Networking::GameBitBuffer* buffer)
{

}
void GameMessage::Encode(Networking::GameBitBuffer* buffer)
{

}
std::string GameMessage::AsText()
{
	return "";
}

GameMessage* GameMessage::ParseMessage(Networking::GameBitBuffer* buffer)
{
	int id = buffer->ReadInt(9);
	Opcodes op = (Opcodes)id;
	GameMessage* msg = 0;
	switch (op)
	{
	case Opcodes::GameSetupMessage:
		msg = new GameSetupMessage(); 
		break;

	case Opcodes::GameTickMessage:
		msg = new GameTickMessage(); 
		break;

	case Opcodes::GameChangeSceneMessage:
		msg = new GameChangeSceneMessage(); 
		break;

	case Opcodes::AttributesSetValuesMessage:
		msg = new AttributesSetValuesMessage();
		break;

	case Opcodes::NewPlayerMessage:
		msg = new NewPlayerMessage();
		break;

	case Opcodes::ACDClientTranslateMessage:
		msg = new ACDClientTranslateMessage();
		break;

	case Opcodes::ACDCreateActorMessage:
		msg = new ACDCreateActorMessage();
		break;

	case Opcodes::ACDDestroyActorMessage:
		msg = new ACDDestroyActorMessage();
		break;

	case Opcodes::ACDEnterMapMessage:
		msg = new ACDEnterMapMessage();
		break;

	case Opcodes::ChatMessage:
		msg = new ChatMessage();
		break;

	case Opcodes::TargetMessage:
		msg = new TargetMessage();
		break;

	case Opcodes::SkillListMessage:
		msg = new SkillListMessage();
		break;

	case Opcodes::AvailableSkillListMessage:
		msg = new AvailableSkillListMessage();
		break;

	case Opcodes::CreateInventoryItemMessage:
		msg = new CreateInventoryItemMessage();
		break;

	case Opcodes::DestroyInventoryItemMessage:
		msg = new DestroyInventoryItemMessage();
		break;

	case Opcodes::InventoryRequestMoveMessage:
		msg = new InventoryRequestMoveMessage();
		break;

	case Opcodes::InventoryResponseMoveMessage:
		msg = new InventoryResponseMoveMessage();
		break;

	case Opcodes::InventoryDropItemMessage:
		msg = new InventoryDropItemMessage();
		break;

	case Opcodes::InventoryShowWindowMessage:
		msg = new InventoryShowWindowMessage();
		break;

	case Opcodes::InventoryCloseWindowMessage:
		msg = new InventoryCloseWindowMessage();
		break;

	case Opcodes::InventoryRequestJewelUse:
		msg = new InventoryRequestJewelUse();
		break;

	case Opcodes::VisualEquipmentMessage:
		msg = new VisualEquipmentMessage();
		break;

	default:
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "no packet with opcode " + Ogre::StringConverter::toString(op));
		return 0;
		//msg = new GameSetupMessage(); 
		//break;
	}

	msg->Parse(buffer);
	return msg;
}
}