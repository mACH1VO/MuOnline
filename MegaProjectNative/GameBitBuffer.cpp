#include "StdAfx.h"
#include "GameBitBuffer.h"

#include "GameMessage.h"
#include "ArrayUtil.h"
#include "BitConverterUtil.h"
#include "EncodingUTF8.h"

using namespace std;
using namespace Messages;

namespace Networking
{

GameBitBuffer::GameBitBuffer(int byteCapacity)
{
	this->Data = new vector<byte>(byteCapacity);
	this->Position = 0;
	this->Length = 0;

	//this->_current_data_len = 0;
	this->_floatBuffer = new byte[4];
}


GameBitBuffer::~GameBitBuffer(void)
{
	//delete this->data;
	delete this->_floatBuffer;
}

void GameBitBuffer::EncodeMessage(GameMessage* msg)
{
	WriteInt(9, (int)msg->opcode);
	msg->Encode(this);
}

vector<byte>* GameBitBuffer::GetPacketAndReset()
{
	int bytes = ((Length + 7) & (~7)) >> 3;
	Position = 0;
	WriteInt(32, bytes);
	//byte[] result = new byte[bytes];
	vector<byte> * result = new vector<byte>(bytes);

	//Array.Copy(Data, result, bytes);
	ArrayUtil::Copy(this->Data, result, bytes);
	Length = 32;
	Position = 32;

	return result;
}

bool GameBitBuffer::CheckAvailable(int length)
{
	return Position + length <= Length;
}
const int BufferAlignment = 31;

void GameBitBuffer::AppendData(vector<byte>* data)
{
	int length = Length >> 3;
	if (length + /*data.Length*/ data->size() > /*Data.Length*/ this->Data->size())
	{
		int newSize = (length + /*data.Length*/data->size() + BufferAlignment) & (~BufferAlignment);
		//Array.Resize(ref Data, newSize);
		this->Data->resize(newSize);
	}
	//Array.Copy(data, 0, Data, length, data.Length);
	ArrayUtil::Copy(data, 0 ,this->Data, length, data->size());
	Length += /*data.Length*/data->size() * 8;
}

void GameBitBuffer::ConsumeData()
{
	int bytes = ((Position + 7) & (~7)) >> 3;
	//Array.Copy(Data, bytes, Data, 0, (Length >> 3) - bytes);
	ArrayUtil::Copy(this->Data, bytes, this->Data, 0 ,(Length >> 3) - bytes);
	Length = Length - (bytes * 8);
	Position = 0;
}


void GameBitBuffer::MakeAvailable(int length)
{
	if (Position + length > this->Data->size() /*Data.Length*/ * 8)
	{
		int newSize = (((Position + length + 7) / 8) + BufferAlignment) & (~BufferAlignment);
		//ArrayUtil::Resize(ref Data, newSize);
		this->Data->resize(newSize);
	}
}

int GameBitBuffer::GetBitCount(int x)
{
	int count = 0;
	while (x > 0)
	{
		x >>= 1;
		count++;
	}
	return count;
}

int GameBitBuffer::GetIntegerValueBitCount(int min, int max)
{
	int x = max - min;
	if (x <= 0)
		return 0; // D3 compat
	return GetBitCount(x);
}

bool GameBitBuffer::IsPacketAvailable()
{
	if (Length - Position < 32)
		return false;
	int pos = Position;
	int packetSize = ReadInt(32);
	Position = pos;
	return CheckAvailable(packetSize * 8);
}

int GameBitBuffer::ReadInt(int length)
{
	if (!CheckAvailable(length))
		Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "EXCEPTION (!CheckAvailable(length)) Not enough bits remaining");
		//throw new GameBitBufferException("Not enough bits remaining.");

	int result = 0;
	while (length > 0)
	{
		int off = Position & 7;
		int count = 8 - off;
		if (count > length)
			count = length;
		int mask = (1 << count) - 1;
		int bits = (Data->at(Position >> 3) >> off);
		result |= (bits & mask) << (length - count);
		length -= count;
		Position += count;
	}
	return result;
}

unsigned int GameBitBuffer::ReadUInt(int length)
{
	return (unsigned int)ReadInt(length);
}

void GameBitBuffer::WriteInt(int length, int value)
{
	MakeAvailable(length);
	while (length > 0)
	{
		int off = Position & 7;
		int count = 8 - off;
		if (count > length)
			count = length;
		int mask = (1 << count) - 1;
		Data->at(Position >> 3) = (byte)((Data->at(Position >> 3) & (~(mask << off))) | (((value >> (length - count)) & mask) << off));
		length -= count;
		Position += count;
		if (Position > Length)
			Length = Position;
	}
}

void GameBitBuffer::WriteInt32(int value)
{
	int length = 32;
	MakeAvailable(length);
	while (length > 0)
	{
		int off = Position & 7;
		int count = 8 - off;
		if (count > length)
			count = length;
		int mask = (1 << count) - 1;
		Data->at(Position >> 3) = (byte)((Data->at(Position >> 3) & (~(mask << off))) | (((value >> (length - count)) & mask) << off));
		length -= count;
		Position += count;
		if (Position > Length)
			Length = Position;
	}
}

void GameBitBuffer::WriteUInt(int length, unsigned int value)
{
	this->WriteInt(length, (int)value);
}


float GameBitBuffer::ReadFloat32()
{
	int value = ReadInt(32);
	 //este puntero no desaparece?
	_floatBuffer[0] = (byte)value;
	_floatBuffer[1] = (byte)((value >> 8) & 0xFF);
	_floatBuffer[2] = (byte)((value >> 16) & 0xFF);
	_floatBuffer[3] = (byte)((value >> 24) & 0xFF);
	return BitConverterUtil::getSingletonPtr()->ToSingle(_floatBuffer, 0);
}

void GameBitBuffer::WriteFloat32(float value)
{
	WriteInt(32, BitConverterUtil::getSingletonPtr()->ToInt32(BitConverterUtil::getSingletonPtr()->GetBytes(value), 0));
}

long GameBitBuffer::ReadInt64(int length)
{
	int count = length >= 32 ? 32 : length;
	long result = ReadInt(count);
	count = length - count;
	if (count > 0)
		result = (result << count) | (long)(unsigned int)ReadInt(count);
	return result;
}

unsigned long GameBitBuffer::ReadUInt64(int length)
{
	return ((unsigned long)ReadInt64(length));
}

void GameBitBuffer::WriteInt64(int length, long value)
{
	MakeAvailable(length);

	if (length <= 32)
	{
		WriteInt(length, (int)(unsigned int)value);
		return;
	}

	int count = length - 32;
	WriteInt(32, (int)(unsigned int)(value >> count));
	WriteInt(count, (int)(unsigned int)value);
}

void GameBitBuffer::WriteUInt64(int length, unsigned long value)
{
	WriteInt64(length, ((long)value));
}

string GameBitBuffer::ReadCharArray(int maxLength)
{
	int size = ReadInt(GetBitCount(maxLength));
	Position = (Position + 7) & (~7);
	if (!CheckAvailable(size * 8))
		Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "EXCEPTION [ReadCharArray] Not enough bits remaining");
		//throw new GameBitBufferException("Not enough bits remaining.");
	string result = EncodingUTF8::GetString(Data, Position >> 3, size);
	//result = std::string(result.begin(), result.end());
	Position += size * 8;
	return result;
}

void GameBitBuffer::WriteCharArray(int maxLength, string value)
{
	//var result = Encoding.UTF8.GetBytes(value);
	std::vector<byte> *result = EncodingUTF8::GetBytes(value);
	WriteInt(GetBitCount(maxLength), /*result.Length*/result->size());
	Position = (Position + 7) & (~7);
	MakeAvailable(/*result.Length*/result->size() * 8);
	//Buffer.BlockCopy(result, 0, Data, Position >> 3, result.Length);
	ArrayUtil::Copy(result, 0, this->Data, Position >> 3, result->size());
	Position += /*result.Length*/ result->size() * 8;
	if (Position > Length)
		Length = Position;

	delete result;
}

bool GameBitBuffer::ReadBool() 
{ 
	return ReadInt(1) != 0; 
}

void GameBitBuffer::WriteBool(bool value) 
{ 
	WriteInt(1, value ? 1 : 0); 
}

vector<byte> * GameBitBuffer::ReadBlob(int sizeBits)
{
	int size = ReadInt(sizeBits);
	//byte[] result = new byte[size];
	vector<byte> * result = new vector<byte>(size);

	Position = (Position + 7) & (~7);
	if (!CheckAvailable(size * 8))
		Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "EXCEPTION [ReadBlob] Not enough bits remaining");
		//throw new GameBitBufferException("Not enough bits remaining.");

	//Buffer.BlockCopy(Data, Position >> 3, result, 0, size);
	ArrayUtil::Copy(Data, Position >> 3, result, 0, size);
	Position += size * 8;
	return result;
}

void GameBitBuffer::WriteBlob(int sizeBits, std::vector<byte>* data)
{
	WriteInt(sizeBits, /*data.Length*/ data->size());
	Position = (Position + 7) & (~7);
	MakeAvailable(/*data.Length*/ data->size() * 8);
	//Buffer.BlockCopy(data, 0, Data, Position >> 3, data.Length);
	ArrayUtil::Copy(data, 0, Data, Position >> 3, /*data.Length*/data->size());

	Position += /*data.Length*/data->size() * 8;
	if (Position > Length)
		Length = Position;
}


float GameBitBuffer::ReadFloat16()
{
	int bits = ReadInt(16);
	int value;
	value = (bits & 0x3FF) << 13;
	value |= (((bits >> 10) & 0x1F) + 112) << 23;
	value |= (bits & 0x8000) << 16;

	_floatBuffer[0] = (byte)value;
	_floatBuffer[1] = (byte)((value >> 8) & 0xFF);
	_floatBuffer[2] = (byte)((value >> 16) & 0xFF);
	_floatBuffer[3] = (byte)((value >> 24) & 0xFF);
	//return BitConverter.ToSingle(_floatBuffer, 0);
	return BitConverterUtil::getSingletonPtr()->ToSingle(_floatBuffer, 0);
}

void GameBitBuffer::WriteFloat16(float value)
{
	//int bits = BitConverter.ToInt32(BitConverter.GetBytes(value), 0);
	int bits = BitConverterUtil::getSingletonPtr()->ToInt32(BitConverterUtil::getSingletonPtr()->GetBytes(value), 0);
	int x = (bits >> 13) & 0x3FF;
	int y = (((bits >> 23) & 0xFF) - 112);
	if (y > 0)
		x |= y << 10;
	x |= (bits >> 16) & 0x8000;
	WriteInt(16, x);
	if (Position > Length)
		Length = Position;
}

}