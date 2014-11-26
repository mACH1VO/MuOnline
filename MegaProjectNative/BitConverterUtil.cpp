#include "StdAfx.h"
#include "BitConverterUtil.h"

template<> BitConverterUtil* Ogre::Singleton<BitConverterUtil>::msSingleton = 0;

BitConverterUtil::BitConverterUtil(void)
{
}


BitConverterUtil::~BitConverterUtil(void)
{
}

float BitConverterUtil::ToSingle(byte *value, int startIndex)
{
	int val = BitConverterUtil::ToInt32(value, startIndex);
	return *(float*)&val;
}

int BitConverterUtil::ToInt32(byte *pbyte, int startIndex)
{
	int Int32 = 0;

		if( startIndex % 4 == 0) 
		{ // data is aligned 
			return *((int *) pbyte);
		}
		else
		{
			throw;
		}

	return Int32;
}


