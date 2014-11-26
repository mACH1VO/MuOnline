#pragma once
#include "stdafx.h"

enum AttributeType;
enum AttributeOpcode;

namespace Game
{
class AAttribute;
class GameAttributeUtil : public Ogre::Singleton<GameAttributeUtil>
{
public:
	GameAttributeUtil(void);
	~GameAttributeUtil(void);

	std::vector<AAttribute*> * AttributesByID;

	AAttribute* getAttribute(int id);
	AttributeType getAttributeTypeByOpcode(AttributeOpcode opcode);
};
}
