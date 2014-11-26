#pragma once
#include "stdafx.h"

namespace Messages
{
	class GameMessage;
}

class TickTimer;
namespace Networking
{

class GameBitBuffer;
//class GameMessage;

class GameClient
{
public:
	GameClient(void);
	~GameClient(void);

	TickTimer* PacketTimer;

	SOCKET ConnectSocket;
	bool isConnected;
	bool isEncrypted;
	bool isInitialized;
	bool isLastMessageGameTick;
	int MessagesReceived;

	bool initialize();
	bool tryConnect(std::string ip, std::string port);

	void tryParseMessages();
	void parse(std::vector<byte>* e);

	void processmessage();

	void update(float timeSinceLastFrame);

	void sendMessage(Messages::GameMessage* gameMessage);

	void FillReadQueue();

	std::queue<Messages::GameMessage*>* _temp_messagesQueue;
	std::queue<Messages::GameMessage*>* toReadmessagesQueue;

private:
	GameBitBuffer* _incomingBuffer;
	GameBitBuffer* _outgoingBuffer;

};
}
