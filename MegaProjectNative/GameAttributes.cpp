#include "StdAfx.h"
#include "GameAttributes.h"

#include "IAttributable.h"
#include "AttributeValue.h"

#include "AAttribute.h"

using namespace Game;

GameAttributes::GameAttributes(IAttributable* _owner)
{
	this->attributeValueMap = new std::map<int, AttributeValue>();
	
}


GameAttributes::~GameAttributes(void)
{
}
