#pragma once
#include "stdafx.h"

class ArrayUtil
{
public:
	ArrayUtil(void);
	~ArrayUtil(void);

    static void Copy(std::vector<byte>* source, int startIndex, std::vector<byte>* dest, int destIndex, int len);
	static void Copy(std::vector<byte>* source, std::vector<byte>* dest, int len );

};

