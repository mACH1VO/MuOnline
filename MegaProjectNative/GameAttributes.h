#pragma once
#include "stdafx.h"

#include "MUEnums.h"
#include "AAttribute.h"
#include "AttributeValue.h"
#include "GameAttributeUtil.h"

#include "AttributeI.h"


namespace Game
{
class IAttributable;

class GameAttributes
{
public:
	GameAttributes(IAttributable* _owner);
	virtual~GameAttributes(void);

	
	IAttributable* owner;
	std::map<int, AttributeValue>* attributeValueMap;
	int operator[] (AttributeI * attributei)
	{ 
		int index = attributei->Id;
		if (this->attributeValueMap->count(index))
		{
			AttributeValue value = this->attributeValueMap->at(index);
			return value.Value;
		}
		return 0;
	}
};
}
