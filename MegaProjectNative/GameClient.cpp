#include "StdAfx.h"
#include "GameClient.h"

#include "TickTimer.h"

#include "GameGlobals.h"
#include "GameBitBuffer.h"
#include "GameMessage.h"
#include "Factory.h"
#include "GameFramework.h"
#include "GameGUI.h"
#include "Chat.h"
#include "Player.h"
#include "Map.h"
#include "PlayerInventory.h"
#include "BaseInventory.h"
#include "InventoryMessageHandler.h"
#include "MUEnums.h"

#include "AttributesSetValuesMessage.h"


#define DEFAULT_BUFLEN 512

namespace Networking
{
GameClient::GameClient(void)
{
	this->_incomingBuffer = new GameBitBuffer(65535);
	this->_outgoingBuffer = new GameBitBuffer(65535);

	this->_outgoingBuffer->WriteInt(32, 0);

	this->isConnected = false;
	this->isEncrypted = false;
	this->isInitialized = false;
	this->MessagesReceived = 0;
	this->ConnectSocket = INVALID_SOCKET;

	this->PacketTimer = new TickTimer(GameGlobals::PACKET_TIMER_MS);

	this->_temp_messagesQueue = new std::queue<Messages::GameMessage*>();
	this->toReadmessagesQueue = new std::queue<Messages::GameMessage*>();
}


GameClient::~GameClient(void)
{
	delete this->_incomingBuffer;
	delete this->_outgoingBuffer;
	delete this->_temp_messagesQueue;
	delete this->toReadmessagesQueue;
}

void GameClient::parse(std::vector<byte>* e)
{
	 this->_incomingBuffer->AppendData(e);

            while (_incomingBuffer->IsPacketAvailable())
            {
                int end = _incomingBuffer->Position;
                end += _incomingBuffer->ReadInt(32) * 8;

                while ((end - _incomingBuffer->Position) >= 9)
                {
                    Messages::GameMessage* message = Messages::GameMessage::ParseMessage(_incomingBuffer);

                    if (message == 0)
                        continue;

					this->MessagesReceived++;
					Ogre::LogManager::getSingletonPtr()->logMessage("[" + Ogre::StringConverter::toString(this->MessagesReceived) + "] " + message->nameClass /*+ " " + message->AsText()*/);
					if (message->opcode == Opcodes::GameTickMessage)
					{
						this->_temp_messagesQueue->push(message);
						//this->isLastMessageGameTick = true;
						this->FillReadQueue();
						//GameFramework::getSingletonPtr()->getFactory()->Consume(message);
					}
					else
					{
						this->_temp_messagesQueue->push(message);
					}
                }

                _incomingBuffer->Position = end;
            }
            _incomingBuffer->ConsumeData();
}

void GameClient::FillReadQueue()
{
	//while (!this->messagesQueue->empty())
	while (!this->_temp_messagesQueue->empty())
            {
                Messages::GameMessage* message = this->_temp_messagesQueue->front();
				this->_temp_messagesQueue->pop();

				this->toReadmessagesQueue->push(message);
				//log stuff
            }
}

bool GameClient::initialize()
{
	WSADATA wsaData;
	
	int iResult;

	// Validate the parameters
	/*if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}*/
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		Ogre::LogManager::getSingletonPtr()->logMessage("WSAStartup failed with error: " + Ogre::StringConverter::toString(iResult));
		return false;
	}

	this->isInitialized = true;
	return true;
}

bool GameClient::tryConnect(std::string ip, std::string port)
{
	int iResult;
	addrinfo hints;
	addrinfo *result = NULL;
	addrinfo *ptr = NULL;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	// Resolve the server address and port
	iResult = getaddrinfo(ip.data(), port.data(), &hints, &result);
	if ( iResult != 0 ) {
		Ogre::LogManager::getSingletonPtr()->logMessage("getaddrinfo failed with error: " + Ogre::StringConverter::toString(iResult));
		WSACleanup();
		//this->isInitialized = false;
		return false;
	}

	ptr = result;
	    // Attempt to connect to an address until one succeeds
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);


		if (ConnectSocket == INVALID_SOCKET) {
			Ogre::LogManager::getSingletonPtr()->logMessage("socket failed with error: " + Ogre::StringConverter::toString(WSAGetLastError()));
			WSACleanup();
			//this->isInitialized = false;
			return false;
		}

		// Connect to server.
		iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			return false;
		}
	

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		Ogre::LogManager::getSingletonPtr()->logMessage("Unable to connect to server!\n");
		WSACleanup();
		//this->isInitialized = false;
		return false;
	}

	this->isConnected = true;
	return true;

	// Send an initial buffer
	/*iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
	if (iResult == SOCKET_ERROR) {
		Ogre::LogManager::getSingletonPtr()->logMessage("send failed with error: " + Ogre::StringConverter::toString(WSAGetLastError()));
		closesocket(ConnectSocket);
		WSACleanup();
		this->isInitialized = false;
		return false;
	}

	printf("Bytes Sent: %ld\n", iResult);*/

	// shutdown the connection since no more data will be sent
	/*iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		Ogre::LogManager::getSingletonPtr()->logMessage("shutdown failed with error: "+  Ogre::StringConverter::toString(WSAGetLastError()));
		closesocket(ConnectSocket);
		WSACleanup();
		return false;
	}
	u_long bytes_available = 0;
	ioctlsocket(ConnectSocket,FIONREAD,&bytes_available);
		if (bytes_available > 0)
		{
			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		}*/
	// Receive until the peer closes the connection
	/*do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if ( iResult > 0 )
			Ogre::LogManager::getSingletonPtr()->logMessage("Bytes received: " + Ogre::StringConverter::toString(iResult));
		else if ( iResult == 0 )
			Ogre::LogManager::getSingletonPtr()->logMessage("Connection closed\n");
		else
			Ogre::LogManager::getSingletonPtr()->logMessage("recv failed with error: " + Ogre::StringConverter::toString(WSAGetLastError()));

	} while( iResult > 0 );*/

	// cleanup
	//closesocket(ConnectSocket);
	//WSACleanup();

	return 0;
}

void GameClient::update(float timeSinceLastFrame)
{
	if (this->isConnected)
		this->tryParseMessages();

	int sizee = this->toReadmessagesQueue->size();

	//if PACKET_TIMER_LIMITER is set, process msg after PACKET_TIMER_MS
	//if not, just take a msg per fps.
	if (GameGlobals::PACKET_TIMER_LIMITER)
	{
		if (this->PacketTimer->TimedOut())
		{
			GameClient::processmessage();
			this->PacketTimer->Reset();
		}
	}
	else
	{
		this->processmessage();
	}
	

}
void GameClient::processmessage()
{
	if (!this->toReadmessagesQueue->empty())
	{
		Messages::GameMessage* message = this->toReadmessagesQueue->front();
		this->toReadmessagesQueue->pop();

		/*if (message->opcode == Opcodes::GameTickMessage)
			break;*/

		//this->MessagesReceived++;

		switch (message->consumer)
		{
		case Consumers::Factory:
			{
				Game::Factory::getSingletonPtr()->Consume(message);
				break;
			}
		case Consumers::Map:
			{
				Game::Map::getSingletonPtr()->Consume(message);
				break;
			}
		case Consumers::Game_:
			{
				//Game::Map::getSingletonPtr()->Consume(message);
				break;
			}
		case Consumers::Player_:
			{
				if (GameFramework::getSingletonPtr()->mainPlayer != 0)
					GameFramework::getSingletonPtr()->mainPlayer->Consume(message);
				//Game::Map::getSingletonPtr()->Consume(message);
				break;
			}
		case Consumers::__Chat:
			{
				GameFramework::getSingletonPtr()->getGameGUI()->getChat()->Consume(message);
				//Game::Map::getSingletonPtr()->Consume(message);
				break;
			}
		case Consumers::Inventory:
			{
				Game::InventoryMessageHandler::Consume(message);
				break;
			}
		case Consumers::attribute_:
			{
				Messages::AttributesSetValuesMessage* msg = (Messages::AttributesSetValuesMessage*)message;
				if (Game::Map::getSingletonPtr()->actorMap->count(msg->ActorID))
				{
					Game::IAttributable* attrib = (Game::IAttributable *)Game::Map::getSingletonPtr()->actorMap->at(msg->ActorID);
					attrib->handleAttributeMessage(msg);
				}

				if (Game::BaseInventory::globalItemsMap.count(msg->ActorID))
				{
					Game::IAttributable* attrib = (Game::IAttributable *)Game::BaseInventory::globalItemsMap.at(msg->ActorID);
					attrib->handleAttributeMessage(msg);
				}
				//Game::Actor::Consume(message);
				break;
			}
		default:
			{
				Ogre::LogManager::getSingleton().logMessage("[Warn] no consumer detected id " + Ogre::StringConverter::toString((int)message->consumer));
				break;
			}
		}
	}
}
void GameClient::tryParseMessages()
{
	if (this->ConnectSocket == INVALID_SOCKET)
		return;

	int iResult;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];

	int recvbuflen = DEFAULT_BUFLEN;

	u_long bytes_available = 0;
	ioctlsocket(this->ConnectSocket, FIONREAD, &bytes_available);
	if (bytes_available > 0)
	{
		iResult = recv(this->ConnectSocket, recvbuf, recvbuflen, 0);

		if( iResult == 0 )
			Ogre::LogManager::getSingletonPtr()->logMessage("Connection closed");

		std::vector<byte> stream(recvbuf, recvbuf + iResult);// = new std::vector<byte>(recvbuf, recvbuf + iResult);
		this->parse(&stream);
		//delete stream;
	}
}

void GameClient::sendMessage(Messages::GameMessage* gameMessage)
{
	this->_outgoingBuffer->EncodeMessage(gameMessage); 
	Ogre::LogManager::getSingletonPtr()->logMessage("[Out] " + gameMessage->nameClass);
	if (_outgoingBuffer->Length <= 32) 
		return;

	std::vector<byte>* data = _outgoingBuffer->GetPacketAndReset();

	if (this->isConnected)
	{
		int iResult = send( ConnectSocket, (char*)data->data(), data->size(), 0 );
		if (iResult == SOCKET_ERROR) {
			Ogre::LogManager::getSingletonPtr()->logMessage("send failed with error: " + Ogre::StringConverter::toString(WSAGetLastError()));
			closesocket(ConnectSocket);
			WSACleanup();
			this->isInitialized = false;
			this->isConnected = false;
			this->isEncrypted = false;
		}
	}
}

}