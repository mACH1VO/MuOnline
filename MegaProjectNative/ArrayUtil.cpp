#include "StdAfx.h"
#include "ArrayUtil.h"


ArrayUtil::ArrayUtil(void)
{
}


ArrayUtil::~ArrayUtil(void)
{
}

void ArrayUtil::Copy(std::vector<byte>* source, int startIndex, std::vector<byte>* dest, int destIndex, int len)
{
	/*std::vector<byte>::iterator it;
	for(it = (source->begin() + startIndex); it != (source->begin() + startIndex + len); it++)
	{
		dest->back(*it);
	}*/
	std::vector<byte>::iterator it_srcIndex = source->begin() + startIndex;
	std::vector<byte>::iterator it_destIndex = dest->begin() + destIndex;

	std::copy( it_srcIndex, it_srcIndex+len, it_destIndex );

	/*std::vector<byte>::iterator it_src = source->begin() + startIndex;
	std::vector<byte> temp = std::vector<byte>(it_src, it_src + len);

	std::vector<byte>::iterator it_dst = dest->begin() + destIndex;
	dest->insert(it_dst, &temp, &temp + len);*/
}

/*void ArrayUtil::Copy(byte* source, int startIndex, std::vector<byte>* dest, int destIndex, int len)
{

}*/

void ArrayUtil::Copy(std::vector<byte>* source, std::vector<byte>* dest, int len )
{
	std::vector<byte>::iterator it_srcIndex = source->begin();
	std::vector<byte>::iterator it_destIndex = dest->begin();

	std::copy( it_srcIndex, it_srcIndex+len, it_destIndex );
}