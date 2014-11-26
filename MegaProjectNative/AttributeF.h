#pragma once
#include "stdafx.h"
#include "AAttribute.h"

enum AttributeEncoding;
namespace Game
{
class AttributeF : public AAttribute
{
public:
	AttributeF(int id, float defaultValue, int u3, int u4, int u5, string scriptA, string scriptB, string name, AttributeEncoding encodingType, byte u10, float min, float max, int bitCount);
	~AttributeF(void);
};
}