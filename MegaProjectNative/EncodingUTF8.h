#pragma once
#include "stdafx.h"
class EncodingUTF8
{
public:
	EncodingUTF8(void);
	~EncodingUTF8(void);
	static std::string GetString(std::vector<byte>* bytes, int index, int count);
	static std::vector<byte>* GetBytes(std::string s);
};

