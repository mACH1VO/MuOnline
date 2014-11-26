#pragma once
#include "stdafx.h"

namespace Game
{
union AttributeValue
{
public:

	int Value;
	float ValueF;

	AttributeValue() 
	{ 
		ValueF = 0; 
		Value = 0; 
	}
	AttributeValue(int value) 
	{ 
		ValueF = 0; 
		Value = value; 
	}

	AttributeValue(float value) 
	{ 
		Value = 0; 
		ValueF = value; 
	}

	inline AttributeValue& operator = ( const AttributeValue& rkAttributeValue )
	{
		this->Value = rkAttributeValue.Value;
		this->ValueF = rkAttributeValue.ValueF;
		return *this;
	}
};
}