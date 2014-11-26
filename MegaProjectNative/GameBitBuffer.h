#pragma once
#include "stdafx.h"

using namespace std;
namespace Messages
{
	class GameMessage;
}

namespace Networking
{
	using namespace Messages;

class GameBitBuffer
{
public:
	GameBitBuffer(int byteCapacity);
	~GameBitBuffer(void);

	void EncodeMessage(GameMessage* msg);

	std::vector<byte>* GetPacketAndReset();
	bool CheckAvailable(int _length);
	void AppendData(std::vector<byte>* data);
	void ConsumeData();
	void MakeAvailable(int length);

	int GetBitCount(int x);
	int GetIntegerValueBitCount(int min, int max);

	bool IsPacketAvailable();

	int ReadInt(int length);
	unsigned int ReadUInt(int length);
	void WriteInt(int length, int value);
	void WriteInt32(int value);
	void WriteUInt(int length, unsigned int value);
	float ReadFloat32();
	void WriteFloat32(float value);
	long ReadInt64(int length);
	unsigned long ReadUInt64(int length);
	void WriteInt64(int length, long value);
	void WriteUInt64(int length, unsigned long value);
	string ReadCharArray(int maxLength);
	void WriteCharArray(int maxLength, string value);
	bool ReadBool();
	void WriteBool(bool value);
	std::vector<byte>* ReadBlob(int sizeBits);
	void WriteBlob(int sizeBits, std::vector<byte>* data);
	float ReadFloat16();
	void WriteFloat16(float value);

	std::vector<byte> *Data;

	int Length;
	int Position;

	

	private:
		byte* _floatBuffer;
};
}
