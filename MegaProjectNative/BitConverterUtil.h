#pragma once
#include "stdafx.h"

class BitConverterUtil: public Ogre::Singleton<BitConverterUtil>
{
public:
	BitConverterUtil(void);
	~BitConverterUtil(void);
	std::queue<byte*> _queuePointers;
	float ToSingle(byte *value, int startIndex);
	int ToInt32(byte* value, int startIndex);
	/*static byte* GetBytes(float value);
	static byte* GetBytes(int value);*/
	inline byte* BitConverterUtil::GetBytes(float value)
	{
		/*int value_2 = (int)(*(int*)&value);

		//byte bytes[4];
		byte* bytes = new byte[4];
		//BitConverterUtil::_clearPointers.push_back(bytes);

		ZeroMemory(bytes, 4);
		byte* b = bytes;
		*((int*)b) = value_2;
		return bytes;*/

		byte* ret = BitConverterUtil::GetBytes((int)(*(int*)&value));
		return ret;
	}

	inline byte* BitConverterUtil::GetBytes(int value)
	{
		//byte bytes[4];
		byte* bytes = new byte[4];
		this->_queuePointers.push(bytes);
		while (this->_queuePointers.size() > 30)
		{
			byte* toDelete = this->_queuePointers.front();
			this->_queuePointers.pop();

			delete toDelete;
		}
		

		ZeroMemory(bytes, 4);
		byte* b = bytes;
		*((int*)b) = value;
		return bytes;
	}

	#if OGRE_DEBUG_MODE

	#else

	#endif
};

