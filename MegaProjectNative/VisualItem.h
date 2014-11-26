#pragma once
#include "stdafx.h"

namespace Networking
{
	class GameBitBuffer;
}
namespace Messages
{
class VisualItem
{
public:
	VisualItem(void);
	~VisualItem(void);

	int snoId;
	int SlotID;
	int Field2;
	int Field3;

	void VisualItem::Parse(Networking::GameBitBuffer* buffer);
	void VisualItem::Encode(Networking::GameBitBuffer* buffer);
	void VisualItem::AsText(std::string b, int pad);
};
};

