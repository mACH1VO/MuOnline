#pragma once
#include "stdafx.h"
#include "AttributeValue.h"

enum AttributeEncoding;
enum AttributeType;
namespace Game
{


class AAttribute
{
public:
	AAttribute(int id, int defaultValue, int u3, int u4, int u5, string scriptA, 
		string scriptB, string name, AttributeEncoding encodingType, byte u10, 
		int min, int max, int bitCount);

	AAttribute(int id, float defaultValue, int u3, int u4, int u5, string scriptA, 
		string scriptB, string name, AttributeEncoding encodingType, byte u10, 
		float min, float max, int bitCount);

	virtual  ~AAttribute(void);

	static const float Float16Min;
	static const float Float16Max;

	int Id;
	AttributeValue _defaultValue;
	int U3;
	int U4;
	int U5;

	string ScriptA;
	string ScriptB;
	string Name;

	AttributeEncoding EncodingType;

	byte U10;

	AttributeValue Min;
	AttributeValue Max;
	int BitCount;

	AttributeType attributeType;


	//bool IsInteger { get { return EncodingType == AttributeEncoding.Int || EncodingType == AttributeEncoding.IntMinMax; } }
	
};
}



