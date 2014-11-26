#pragma once
#include "stdafx.h"

namespace Messages
{
	class AttributesSetValuesMessage;
}

enum AttributeOpcode;

namespace Game
{
class GameAttributes;
class IAttributable
{
public:
	IAttributable(void);
	virtual ~IAttributable(void) ;

	//GameAttributes* Attributes;

	std::vector<AttributeOpcode> *currentAttributes;

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);
};
}

