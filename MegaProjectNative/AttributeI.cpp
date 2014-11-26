#include "StdAfx.h"
#include "AttributeI.h"
#include "MUEnums.h"

using namespace Game;

AttributeI::AttributeI(int id, int defaultValue, int u3, int u4, int u5, string scriptA, string scriptB, string name, AttributeEncoding encodingType, byte u10, int min, int max, int bitCount)
	: AAttribute(id, defaultValue, u3, u4, u5, scriptA, scriptB, name, encodingType, u10, min, max, bitCount)
{
	this->attributeType = AttributeType::Integer;
}


AttributeI::~AttributeI(void)
{
}
