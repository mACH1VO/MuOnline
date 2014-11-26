#include "StdAfx.h"
#include "AAttribute.h"
#include "AttributeValue.h"
#include "MUEnums.h"

using namespace Game;
const float AAttribute::Float16Max = 65536.0f;
const float AAttribute::Float16Min = -65536.0f;

AAttribute::AAttribute(int id, int defaultValue, int u3, int u4, int u5, string scriptA, string scriptB, string name, AttributeEncoding encodingType, byte u10, int min, int max, int bitCount)
{
	this->Id = id;
	this->_defaultValue = AttributeValue(defaultValue);
	this->U3 = u3;
	this->U4 = u4;
	this->U5 = u5;
	this->ScriptA = scriptA;
	this->ScriptB = scriptB;
	this->Name = name;
	this->EncodingType = encodingType;
	this->U10 = u10;

	this->Min = AttributeValue(min);//= new AttributeValue(min);
	this->Max = AttributeValue(max); //= new AttributeValue(max);
	this->BitCount = bitCount;
}

AAttribute::AAttribute(int id, float defaultValue, int u3, int u4, int u5, string scriptA, string scriptB, string name, AttributeEncoding encodingType, byte u10, float min, float max, int bitCount)
{
	this->Id = id;
	this->_defaultValue = AttributeValue(defaultValue); //= new AttributeValue(defaultValue);
	this->U3 = u3;
	this->U4 = u4;
	this->U5 = u5;
	this->ScriptA = scriptA;
	this->ScriptB = scriptB;
	this->Name = name;
	this->EncodingType = encodingType;
	this->U10 = u10;

	this->Min = AttributeValue(min);//= new AttributeValue(min);
	this->Max = AttributeValue(max);  //= new AttributeValue(max);

	this->BitCount = bitCount;
}

AAttribute::~AAttribute(void)
{
	/*delete this->_defaultValue;
	delete this->Min;
	delete this->Max;*/
}
