#include "StdAfx.h"
#include "EncodingUTF8.h"


EncodingUTF8::EncodingUTF8(void)
{
}


EncodingUTF8::~EncodingUTF8(void)
{
}

std::string EncodingUTF8::GetString(std::vector<byte>* bytes, int index, int count)
{
	std::vector<char> bytes_char = std::vector<char>(bytes->begin() + index, bytes->begin()+ index+count);
	std::string ret = std::string(bytes_char.begin(), bytes_char.end());
	return ret;
}

std::vector<byte>* EncodingUTF8::GetBytes(std::string s)
{
	std::vector<byte>* ret = new std::vector<byte>(s.begin(), s.end());
	return ret;
}