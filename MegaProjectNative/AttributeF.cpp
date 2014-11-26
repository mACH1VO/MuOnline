#include "StdAfx.h"
#include "AttributeF.h"
#include "MUEnums.h"

using namespace Game;

AttributeF::AttributeF(int id, float defaultValue, int u3, int u4, int u5, string scriptA, string scriptB, string name, AttributeEncoding encodingType, byte u10, float min, float max, int bitCount)
	: AAttribute(id, defaultValue, u3, u4, u5, scriptA, scriptB, name, encodingType, u10, min, max, bitCount)
{
	this->attributeType = AttributeType::Float;
}


AttributeF::~AttributeF(void)
{
}
